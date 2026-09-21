/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:23:34 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:23:36 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

int	is_numeric_token(char *s)
{
	int	i;
	int	dots;
	int	digits;

	i = 0;
	dots = 0;
	digits = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] == '.')
			dots++;
		else if (ft_isdigit(s[i]))
			digits++;
		else
			return (0);
		i++;
	}
	return (dots <= 1 && digits > 0);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

t_vec3	parse_vec3(char *s, t_rt *rt)
{
	char	**split;
	t_vec3	v;
	int		i;

	split = ft_split(s, ',');
	if (!split)
		msg_exit("calloc failure", rt);
	i = 0;
	while (split[i])
		i++;
	if (i != 3 || !is_numeric_token(split[0]) || !is_numeric_token(split[1])
		|| !is_numeric_token(split[2]))
		msg_exit("expected 3 comma-separated numbers", rt);
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	free_split(split);
	return (v);
}

static int	is_rgb_token(char *s)
{
	int	i;

	i = 0;
	if (!ft_isdigit(s[i]))
		return (0);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] || i > 3)
		return (0);
	return (ft_atoi(s) <= RGB_U);
}

t_color	parse_color(char *s, t_rt *rt)
{
	char	**split;
	t_color	c;
	int		i;

	split = ft_split(s, ',');
	if (!split)
		msg_exit("calloc failure", rt);
	i = 0;
	while (split[i])
		i++;
	if (i != 3 || !is_rgb_token(split[0]) || !is_rgb_token(split[1])
		|| !is_rgb_token(split[2]))
		msg_exit("expected 3 comma-separated RGB values in [0,255]", rt);
	c.r = ft_atoi(split[0]) / 255.0;
	c.g = ft_atoi(split[1]) / 255.0;
	c.b = ft_atoi(split[2]) / 255.0;
	free_split(split);
	return (c);
}
