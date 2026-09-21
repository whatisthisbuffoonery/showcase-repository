/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:09:26 by achew             #+#    #+#             */
/*   Updated: 2026/08/22 15:12:15 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

int	correct_file_type(char *file)
{
	int	len;

	len = ft_strlen(file);
	return (!ft_strncmp(file + len - 3, ".rt", 3));
}
