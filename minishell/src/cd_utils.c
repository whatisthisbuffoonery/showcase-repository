/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:10 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:10 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//assumes dst is always to the left of src
void	path_strmove(char *dst, int n)
{
	int		i;
	char	*src;

	if (!dst || n <= 0)
		return ;
	i = 0;
	src = &dst[n];
	while (1)
	{
		dst[i] = src[i];
		if (!dst[i])
			break ;
		i ++;
	}
}

void	path_process(char *v)
{
	int	i;
	int	k;

	i = 0;
	while (v[i])
	{
		k = 0;
		while (v[i] && v[i] != '/')
			i ++;
		i += (v[i] == '/');
		while (v[i + k] && v[i + k] == '/')
			k ++;
		path_strmove(&v[i], k);
		i += (v[i] != '\0');
	}
}

void	remove_component(char *str, int *src)
{
	int	i;
	int	index;

	i = 0;
	if (src)
		index = *src;
	else
	{
		index = ft_strlen(str) - 1;
		while (index > 0 && str[index - 1] != '/')
			index --;
	}
	while (str[index + i] && str[index + i] != '/')
		i ++;
	if (!i)
		return ;
	i += (str[index + i] == '/');
	path_strmove(&str[index], i);
	index -= (index > 0 && str[index - 1] == '/') + (index > 1);
	while (index > 0 && str[index - 1] != '/')
		index --;
	if (src)
		*src = index;
}

int	resolve_relative(char *pwd, int *src)
{
	int	i;
	int	index;

	i = 0;
	index = *src;
	if (!pwd[index] || (pwd[index] == '/' && !pwd[index + 1]))
		return (1);
	while (pwd[i + index] && pwd[i + index] != '/')
		i ++;
	if (pwd[index] == '.' && pwd[index + 1] == '.' && i == 2)
	{
		remove_component(pwd, src);
		if (index > 1)
			remove_component(pwd, src);
	}
	else if (pwd[index] == '.' && i == 1)
		path_strmove(&pwd[index], i + (pwd[index + i] == '/'));
	else
		*src += i + (pwd[index + i] == '/');
	return (0);
}

int	new_pwd(char *pwd, char *v)
{
	int			i;
	int			done;

	if (v[0] == '/')
	{
		ft_strlcpy(pwd, v, -1);
		return (builtin_err(-1 * access(pwd, X_OK), "cd", v));
	}
	path_process(pwd);
	i = ft_strlen(pwd);
	if (pwd[i - 1] != '/')
	{
		i ++;
		ft_strlcat(pwd, "/", -1);
	}
	ft_strlcat(pwd, v, -1);
	path_process(pwd);
	done = builtin_err(access(pwd, X_OK), "cd", v);
	while (!done)
		done = resolve_relative(pwd, &i);
	return (done < 0);
}
