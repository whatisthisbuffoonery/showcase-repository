/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:21:22 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:21:28 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

int	parse_light(char **tokens, int i, t_rt *rt)
{
	char	*brightness_tok;
	t_light	*light;

	if (rt->scene.lights && !rt->is_bonus)
		msg_exit("L: light can only be declared once", rt);
	light = light_new();
	if (!light)
		msg_exit("malloc failure", rt);
	light_add_back(&rt->scene.lights, light);
	light->pos = parse_vec3(require_token(tokens, i + 1, rt), rt);
	brightness_tok = require_token(tokens, i + 2, rt);
	if (!is_numeric_token(brightness_tok))
		msg_exit("L: brightness: non-numeric value", rt);
	light->brightness = ft_atof(brightness_tok);
	if (light->brightness < L_BRIGHTNESS_L
		|| light->brightness > L_BRIGHTNESS_U)
		msg_exit("L: brightness out of range [0,1]", rt);
	light->color = parse_color(require_token(tokens, i + 3, rt), rt);
	return (i + 4);
}
