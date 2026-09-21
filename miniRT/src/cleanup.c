/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:05:25 by achew             #+#    #+#             */
/*   Updated: 2026/08/22 15:05:32 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

static void	free_objects(t_object *lst)
{
	t_object	*next;

	while (lst)
	{
		next = lst->next;
		if (lst->caps)
			free_objects(lst->caps);
		free(lst);
		lst = next;
	}
}

static void	free_lights(t_light *lst)
{
	t_light	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
}

void	free_scene(t_rt *rt)
{
	free_objects(rt->scene.objects);
	rt->scene.objects = NULL;
	free_lights(rt->scene.lights);
	rt->scene.lights = NULL;
}

void	free_rt(t_rt *rt)
{
	if (!rt)
		return ;
	free_scene(rt);
	if (rt->tokens)
		free_tokens(rt->tokens);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->img)
		mlx_destroy_image(rt->mlx, rt->img);
	if (rt->mlx)
		mlx_destroy_display(rt->mlx);
	free(rt->mlx);
	free(rt);
}

int	clicked_x(void *param)
{
	mlx_loop_end(((t_rt *) param)->mlx);
	return (0);
}
