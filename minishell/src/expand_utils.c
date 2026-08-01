/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:35 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:35 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	copy_wrapper(char *src, char *dst, int *i, int *len)
{
	if (dst)
		dst[*len] = src[*i];
	*i += 1;
	*len += 1;
}

int	concat_wrapper(t_tok *dst, t_env *env, char *ret, int *i)
{
	char	*src;
	char	*str;
	int		k;
	int		tmp_len;

	k = 0;
	str = &dst->str[*i + 1];
	tmp_len = 0;
	while (isenv(str[k]))
		k ++;
	src = find_env_str(str, env, k);
	if (ret && src)
		ft_strlcat(ret, src, -1);
	if (src)
		tmp_len += ft_strlen(src);
	*i += k + (str[0] == '?') + 1;
	return (tmp_len);
}

//we copy dollar sign if env name is invalid
int	use_expansion(t_tok *dst, t_env *env, char *ret)
{
	int		i;
	int		len;
	char	*err_msg;

	i = 0;
	len = 0;
	err_msg = "env expansion malloc";
	if (ret)
		ret[0] = '\0';
	while (dst->str[i])
	{
		if (envname(&dst->str[i]))
			len += concat_wrapper(dst, env, ret, &i);
		else
			copy_wrapper(dst->str, ret, &i, &len);
	}
	if (!ret
		&& (!ft_err(-!malloc_cond((void **) &ret, len + 1), err_msg)))
		return (use_expansion(dst, env, ret));
	else if (!ret)
		return (1);
	free(dst->str);
	dst->str = ret;
	return (0);
}

int	expand_word(t_tok *iter, t_env *env)
{
	while (iter)
	{
		if (iter->type != '\'' && ft_strchr(iter->str, '$')
			&& use_expansion(iter, env, NULL))
			return (1);
		iter = iter->word_next;
	}
	return (0);
}

int	expand_str(t_tok *iter, t_env *env)
{
	while (iter)
	{
		if (expand_word(iter, env))
			return (1);
		iter = iter->next;
	}
	return (0);
}
