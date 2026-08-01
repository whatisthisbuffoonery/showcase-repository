/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 21:19:28 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/19 21:19:30 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	check_terminal(struct termios *term)
{
	int	cond[2];

	cond[0] = tcgetattr(0, &term[2]);
	cond[1] = 1;
	if (!cond[0])
	{
		cond[1] = 0;
		cond[1] += (term[1].c_lflag != term[2].c_lflag);
		cond[1] += (term[1].c_cc[VMIN] != term[2].c_cc[VMIN]);
		cond[1] += (term[1].c_cc[VTIME] != term[2].c_cc[VTIME]);
	}
	if (cond[1])
		errno = (0 * !cond[0]) + (errno * (cond[0] != 0));
	return (cond[1]);
}

//cant emit errors itself due to terminal attr
int	query_terminal(void)
{
	int		i;
	int		k;
	int		len;
	char	*query;

	query = "\033[6n";
	len = ft_strlen(query);
	i = 0;
	while (i < len)
	{
		k = write(1, &query[i], len - i);
		if (k < 0 && errno != EINTR)
			return (1);
		i += k;
	}
	return (0);
}

//do not consider sigint
int	check_nl(void)
{
	int		read_col;
	int		col;
	int		len;
	char	buf;

	buf = '\0';
	read_col = 0;
	col = 0;
	if (query_terminal())
		return (-1);
	while (1)
	{
		len = read(0, &buf, 1);
		if ((len < 0 && errno != EINTR) || !len || buf == 'R')
		{
			col = (col * (buf == 'R')) - (buf != 'R');
			break ;
		}
		else if (!read_col && buf != ';')
			continue ;
		read_col = 1;
		col = (col * 10) + (buf - '0');
	}
	return (col);
}

void	nl_err(int result, char *err_str)
{
	if (result >= 0)
		return ;
	else if (errno)
		ft_err(-1, err_str);
	else
		shell_assert(1, err_str);
}

//not my dumbass forgetting to memset term reeeee
void	replace_nl(void)
{
	struct termios	term[3];
	char			*err_str;
	int				result;

	err_str = "error while checking terminal display";
	ft_memset(term, 0, 3 * sizeof(struct termios));
	if (ft_err(tcgetattr(0, &term[0]), err_str))
		return ;
	term[1] = term[0];
	term[1].c_lflag &= (~ICANON & ~ECHO);
	term[1].c_cc[VMIN] = 0;
	term[1].c_cc[VTIME] = 1;
	result = 0;
	if (ft_err(tcsetattr(0, TCSANOW, &term[1]), err_str))
		return ;
	else if (!check_terminal(term))
		result = check_nl();
	ft_err(tcsetattr(0, TCSANOW, &term[0]), "error restoring terminal");
	if (result > 1)
		ft_putchar('\n');
	nl_err(result, err_str);
}
