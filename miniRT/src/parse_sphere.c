/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:22:23 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:22:25 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

int	parse_sphere(char **tokens, int i, t_rt *rt)
{
	char		*diameter_tok;
	t_object	*obj;

	obj = object_new(OBJ_SPHERE);
	if (!obj)
		msg_exit("malloc failure", rt);
	object_add_back(&rt->scene.objects, obj);
	obj->pos = parse_vec3(require_token(tokens, i + 1, rt), rt);
	diameter_tok = require_token(tokens, i + 2, rt);
	if (!is_numeric_token(diameter_tok))
		msg_exit("sp: diameter: non-numeric value", rt);
	obj->diameter = ft_atof(diameter_tok);
	if (obj->diameter <= 0)
		msg_exit("sp: diameter must be positive", rt);
	obj->radius = obj->diameter / 2.0;
	obj->radius_sq = obj->radius * obj->radius;
	obj->inv_radius = 1.0 / obj->radius;
	obj->material.color = parse_color(require_token(tokens, i + 3, rt), rt);
	return (i + 4);
}
