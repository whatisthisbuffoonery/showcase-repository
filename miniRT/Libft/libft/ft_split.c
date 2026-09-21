/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:06:34 by achew             #+#    #+#             */
/*   Updated: 2025/11/30 15:19:41 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char d, char c)
{
	if (c == d)
		return (1);
	return (0);
}

static int	get_array_len(char const *str, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], c) == 1)
			i++;
		else
		{
			len++;
			while (str[i] != '\0' && is_sep(str[i], c) == 0)
				i++;
		}
	}
	return (len);
}

static int	count_char(char const *str, char c, unsigned int *i_ptr)
{
	int	char_count;

	char_count = 0;
	while ((str[*i_ptr] != '\0') && (is_sep(str[*i_ptr], c) == 0))
	{
		char_count++;
		(*i_ptr)++;
	}
	(*i_ptr) -= char_count;
	return (char_count);
}

static char	**fill_array(char **array, char const *str, char c)
{
	unsigned int	i;
	unsigned int	j;
	size_t			char_count;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], c) == 1)
			i++;
		else
		{
			char_count = count_char(str, c, &i);
			array[j] = ft_substr(str, i, char_count);
			if (!array[j])
			{
				while (j > 0)
					free(array[--j]);
				return (NULL);
			}
			i += char_count;
			j++;
		}
	}
	return (array[j] = NULL, array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		array_len;

	if (!s)
		return (NULL);
	array_len = get_array_len(s, c);
	array = malloc((array_len + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	if (fill_array(array, s, c) == NULL)
	{
		free(array);
		return (NULL);
	}
	return (array);
}
