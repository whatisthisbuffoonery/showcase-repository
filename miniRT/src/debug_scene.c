/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:26:27 by achew             #+#    #+#             */
/*   Updated: 2026/09/04 17:08:23 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

//wait we dont have cuboids
static char	*obj_type_name(t_obj_type type)
{
	if (type == OBJ_SPHERE)
		return ("sphere");
	if (type == OBJ_PLANE)
		return ("plane");
	if (type == OBJ_CYLINDER)
		return ("cylinder");
	return ("cone");
}

static void	print_objects(t_object *obj)
{
	while (obj)
	{
		printf("  %s: pos=(%g,%g,%g) dir=(%g,%g,%g) diam=%g height=%g"
			" color=(%g,%g,%g)\n", obj_type_name(obj->type),
			obj->pos.x, obj->pos.y, obj->pos.z,
			obj->dir.x, obj->dir.y, obj->dir.z, obj->diameter, obj->height,
			obj->material.color.r, obj->material.color.g,
			obj->material.color.b);
		obj = obj->next;
	}
}

static void	print_lights(t_light *light)
{
	while (light)
	{
		printf("  light: pos=(%g,%g,%g) brightness=%g color=(%g,%g,%g)\n",
			light->pos.x, light->pos.y, light->pos.z, light->brightness,
			light->color.r, light->color.g, light->color.b);
		light = light->next;
	}
}

void	display_scene(t_scene *scene)
{
	printf("ambient: ratio=%g color=(%g,%g,%g)\n", scene->ambient_ratio,
		scene->ambient_color.r, scene->ambient_color.g,
		scene->ambient_color.b);
	printf("camera: pos=(%g,%g,%g) dir=(%g,%g,%g) fov=%g\n",
		scene->camera.pos.x, scene->camera.pos.y, scene->camera.pos.z,
		scene->camera.dir.x, scene->camera.dir.y, scene->camera.dir.z,
		scene->camera.fov);
	printf("lights:\n");
	print_lights(scene->lights);
	printf("objects:\n");
	print_objects(scene->objects);
}
