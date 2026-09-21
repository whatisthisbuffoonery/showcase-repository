/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:31:29 by achew             #+#    #+#             */
/*   Updated: 2025/11/29 23:11:04 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_array_len_recursive(long long nb_long, size_t *count_ptr)
{
	if (nb_long >= 10)
	{
		(*count_ptr)++;
		get_array_len_recursive(nb_long / 10, count_ptr);
	}
	return (*count_ptr + 1);
}

static size_t	get_array_len(int n)
{
	long long	nb_long;
	size_t		count;

	nb_long = n;
	count = 0;
	if (nb_long < 0)
	{
		count++;
		nb_long *= -1;
	}
	return (get_array_len_recursive(nb_long, &count));
}

static char	*write_array_recursive(long long nb_long,
		char *array, size_t *i_ptr)
{
	char		c;

	if (nb_long >= 10)
	{
		write_array_recursive(nb_long / 10, array, i_ptr);
	}
	c = nb_long % 10 + '0';
	array[(*i_ptr)++] = c;
	return (array);
}

static char	*write_array(int n, char *array)
{
	long long	nb_long;
	size_t		i;

	i = 0;
	nb_long = n;
	if (nb_long < 0)
	{
		array[i++] = '-';
		nb_long *= -1;
	}
	return (write_array_recursive(nb_long, array, &i));
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*result;

	len = get_array_len(n);
	result = (char *)malloc((len + 1) * sizeof(char));
	result[len] = '\0';
	if (result)
		write_array(n, result);
	return (result);
}
