/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:22:57 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:23:00 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

int	parse_ambient(char **tokens, int i, t_rt *rt)
{
	char	*ratio_tok;
	char	*color_tok;

	if (rt->scene.has_ambient)
		msg_exit("A: ambient lighting can only be declared once", rt);
	ratio_tok = require_token(tokens, i + 1, rt);
	color_tok = require_token(tokens, i + 2, rt);
	if (!is_numeric_token(ratio_tok))
		msg_exit("A: ambient ratio: non-numeric value", rt);
	rt->scene.ambient_ratio = ft_atof(ratio_tok);
	if (rt->scene.ambient_ratio < A_LIGHT_RATIO_L
		|| rt->scene.ambient_ratio > A_LIGHT_RATIO_U)
		msg_exit("A: ambient ratio out of range [0,1]", rt);
	rt->scene.ambient_color = parse_color(color_tok, rt);
	rt->scene.has_ambient = 1;
	return (i + 3);
}
