/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:23:11 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:23:14 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

static int	tok_eq(char *tok, char *id)
{
	return (ft_strncmp(tok, id, ft_strlen(id) + 1) == 0);
}

static int	dispatch_one(char **tokens, int i, t_rt *rt)
{
	/*TODO see if user normal/direction is normalised*/
	if (tok_eq(tokens[i], "A"))
		return (parse_ambient(tokens, i, rt));
	else if (tok_eq(tokens[i], "C"))
		return (parse_camera(tokens, i, rt));
	else if (tok_eq(tokens[i], "L"))
		return (parse_light(tokens, i, rt));
	else if (tok_eq(tokens[i], "sp"))
		return (parse_sphere(tokens, i, rt));
	else if (tok_eq(tokens[i], "pl"))
		return (parse_plane(tokens, i, rt));
	else if (tok_eq(tokens[i], "cy"))
		return (parse_cylinder(tokens, i, rt));
	else if (rt->is_bonus && tok_eq(tokens[i], "co"))
		return (parse_cone(tokens, i, rt));
	msg_exit("unknown element identifier in scene file", rt);
	return (i);
}

void	parse_tokens(char **tokens, t_rt *rt)
{
	int	i;

	i = 0;
	while (tokens[i])
		i = dispatch_one(tokens, i, rt);
	if (!rt->scene.has_ambient)
		msg_exit("missing required ambient lighting element (A)", rt);
	if (!rt->scene.has_camera)
		msg_exit("missing required camera element (C)", rt);
}
