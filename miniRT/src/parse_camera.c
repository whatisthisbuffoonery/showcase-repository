/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:22:41 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:22:45 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

int	parse_camera(char **tokens, int i, t_rt *rt)
{
	char	*fov_tok;

	if (rt->scene.has_camera)
		msg_exit("C: camera can only be declared once", rt);
	rt->scene.camera.pos = parse_vec3(require_token(tokens, i + 1, rt), rt);
	rt->scene.camera.dir = parse_vec3(require_token(tokens, i + 2, rt), rt);
	if (!vec_in_range(rt->scene.camera.dir, VECTOR_L, VECTOR_U))
		msg_exit("C: orientation vector components must be in [-1,1]", rt);
	else if (vec_dot(rt->scene.camera.dir, rt->scene.camera.dir) < EPSILON_SQ)
		msg_exit("C: nonzero direction needed", rt);
	rt->scene.camera.dir = vec_norm(rt->scene.camera.dir);
	fov_tok = require_token(tokens, i + 3, rt);
	if (!is_numeric_token(fov_tok))
		msg_exit("C: FOV: non-numeric value", rt);
	rt->scene.camera.fov = ft_atof(fov_tok);
	if (rt->scene.camera.fov < C_FOV_L || rt->scene.camera.fov > C_FOV_U)
		msg_exit("C: FOV out of range [0,180]", rt);
	rt->scene.has_camera = 1;
	return (i + 4);
}
