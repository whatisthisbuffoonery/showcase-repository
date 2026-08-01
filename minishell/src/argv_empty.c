/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_empty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:30:28 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/17 18:30:30 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//ft_printf("loop start: argv[%s],
//src[%s], type[%c]\n", argv[i], src->str, src->type);
//
//ft_printf("loop end: argv[%s], src[%s]\n", argv[i], src?src->str:"null");
void	argv_remove_empty(char **argv, t_tok *src)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i] && src)
	{
		align_argv(argv, &i, &src);
		if (!src)
			return ;
		if (!argv[i][0] && !argv_check_quote(src))
			move_argv(&argv[i]);
		else
			i ++;
		src = src->next;
	}
}
