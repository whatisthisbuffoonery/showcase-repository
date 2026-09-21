/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:02:31 by achew             #+#    #+#             */
/*   Updated: 2025/11/29 23:07:43 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ctype.h>

//int	ft_isupper(int c)
//{
//	if (c >= 'A' && c <= 'Z')
//		return (1);
//	return (0);
//}
//
static int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	ft_toupper(int c)
{
	if (ft_islower(c))
	{
		c -= 32;
		return (c);
	}
	return (c);
}
