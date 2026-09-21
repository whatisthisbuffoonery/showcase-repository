/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:23:46 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:23:48 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

void	configure_plane(t_object *obj, int *i)
{
	if (obj->pl_type == ROUND)
	{
		obj->radius = obj->diameter / 2.0;
		obj->radius_sq = obj->radius * obj->radius;
		//plane case doesnt use inv_radius...?
		*i += 1;
	}
	else if (obj->pl_type == RECTANGLE)
	{
		obj->half_w = obj->width / 2.0;
		obj->half_h = obj->height / 2.0;
		*i += 2;
	}
}

void	plane_dimensions(t_object *obj, char **token, t_rt *rt)
{
	int		i;
	int		lim;
	char	*tok[2];

	lim = 1 + (obj->pl_type == RECTANGLE);
	i = 0;
	while (i < lim)
	{
		tok[i] = require_token(token, i, rt);
		if (!is_numeric_token(tok[i++]))
			msg_exit("pl: extra parameter NAN", rt);
	}
	if (obj->pl_type == RECTANGLE)
	{
		obj->width = ft_atof(tok[0]);
		obj->height = ft_atof(tok[1]);
		if (obj->width <= 0 || obj->height <= 0)
			msg_exit("pl: width and height must be greater than 0", rt);
	}
	else if (obj->pl_type == ROUND)
	{
		obj->diameter = ft_atof(tok[0]);
		if (obj->diameter <= 0)
			msg_exit("pl: radius must be greater than 0", rt);
	}
}

void	plane_UVN(t_vec3 *U, t_vec3 *V, t_vec3 N)//should cache at init
{
	t_vec3	A;

	A = (t_vec3){.x = !(fabs(N.x) > 0.9f), .y = (fabs(N.x) > 0.9f), .z = 0};
	*U = vec_norm(vec_cross(N, A));
	*V = vec_norm(vec_cross(N, *U));
}

void	set_plane_type(t_object *obj, int *i, char **token, t_rt *rt)
{
	if (!*token)
		return ;
	else if (!ft_strcmp(*token, "inf"))
	{
		*i += 1;
		return ;
	}
	else if (!ft_strcmp(*token, "round"))
		obj->pl_type = ROUND;
	else if (!ft_strcmp(*token, "rec"))
		obj->pl_type = RECTANGLE;
	else
		return ;
	plane_dimensions(obj, &token[1], rt);
	configure_plane(obj, i);
}

int	parse_plane(char **tokens, int i, t_rt *rt)
{
	t_object	*obj;

	obj = object_new(OBJ_PLANE);
	if (!obj)
		msg_exit("calloc failure", rt);
	object_add_back(&rt->scene.objects, obj);
	obj->pos = parse_vec3(require_token(tokens, i + 1, rt), rt);
	obj->dir = parse_vec3(require_token(tokens, i + 2, rt), rt);
	if (!vec_in_range(obj->dir, VECTOR_L, VECTOR_U))
		msg_exit("pl: normal vector components must be in [-1,1]", rt);
	else if (vec_dot(obj->dir, obj->dir) < EPSILON_SQ)
		msg_exit("pl: nonzero direction needed", rt);
	obj->dir = vec_norm(obj->dir);
	obj->material.color = parse_color(require_token(tokens, i + 3, rt), rt);
	obj->N = obj->dir;
	obj->pl_type = INFINITE;
	set_plane_type(obj, &i, &tokens[i + 4], rt);//exits on error
	plane_UVN(&obj->U, &obj->V, obj->N);
	obj->offset = -vec_dot(obj->pos, obj->dir);
	return (i + 4);
}
