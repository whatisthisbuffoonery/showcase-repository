/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fmt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:28:36 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 18:08:53 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_fmt(const char *str, const char *array)
{
	int			fmt_len;
	int			i;
	const char	*temp;

	temp = str;
	fmt_len = 0;
	i = 0;
	while (*str && array[i])
	{
		if (*str == array[i])
		{
			fmt_len++;
			i = 0;
			str++;
		}
		else
			i++;
	}
	(void) temp;
	return (fmt_len);
}

static int	has_fmt(const char *str, const char *array)
{
	int	i;

	i = 0;
	while (*str && array[i])
	{
		if (*str == array[i])
			return (1);
		i++;
	}
	return (0);
}

int	*is_fmt(const char *str)
{
	int	*fmt_counts;

	fmt_counts = (int *)malloc(4 * sizeof(int));
	if (!fmt_counts)
		return (NULL);
	if (*str == '%')
	{
		fmt_counts[1] = count_fmt(str + 1, FLAGS);
		fmt_counts[2] = count_fmt(str + fmt_counts[1] + 1, DIGITS);
		fmt_counts[3] = 0;
		if (*(str + fmt_counts[1] + fmt_counts[2] + 1) == '.')
		{
			fmt_counts[3] = 1;
			fmt_counts[3] += count_fmt(str + fmt_counts[1] + fmt_counts[2] + 2,
					DIGITS);
		}
		if (has_fmt(str + fmt_counts[1] + fmt_counts[2] + fmt_counts[3] + 1,
				SPECIFIER))
		{
			fmt_counts[0] = fmt_counts[1] + fmt_counts[2] + fmt_counts[3] + 1;
			return (fmt_counts);
		}
	}
	free(fmt_counts);
	return (NULL);
}
