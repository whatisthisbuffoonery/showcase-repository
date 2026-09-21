/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 16:36:17 by achew             #+#    #+#             */
/*   Updated: 2026/09/04 22:22:29 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

/*

implement planes:
	single sided: if (dot(N, D) >= 0) declare miss (greater equal) //meh might do
	double sided: if (dot(N, D) > 0) flip all terms of N (greater not equal)

consider AABB culling when the above is finished
*/

int	main(int argc, char **argv)
{
	t_rt	*rt;

	if (argc != 2 || !correct_file_type(argv[1]))
	{
		ft_putstr_fd("Usage: ./miniRT *.rt\n", 2);
		return (1);
	}
	rt = init_rt();
	if (!rt)
		return (1);
	rt->is_bonus = mand_or_bonus();
	printf("bonus?: %d\n", rt->is_bonus);
	tokenize_file(argv[1], rt);
	parse_tokens(rt->tokens, rt);
	ft_printf("=====\nscene description given:\n");
	display_scene(&rt->scene);
	ft_printf("\n=====\n");
	//quaternion_simulation(rt);
	if (!rt_mlx(rt, argv))
		loop_me(rt);
	free_rt(rt);
	return (0);
}
