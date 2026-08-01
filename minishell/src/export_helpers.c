/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:37:27 by achew             #+#    #+#             */
/*   Updated: 2026/06/16 16:14:55 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	update_val(char *val, t_shnode *existing)
{
	char	*new_str;

	new_str = ft_strdup(val);
	if (!new_str)
		return (1);
	free(existing->str);
	existing->str = new_str;
	return (0);
}

int	invalid_var(char *var)
{
	int		i;

	if (!var || !var[0])
		return (1);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (1);
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	invalid_identifier(char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

void	escape_double_quotes(t_shnode *export, int out)
{
	char	*double_quote;
	int		i;
	int		n;

	double_quote = ft_strchr(export->str, '"');
	i = 0;
	while (double_quote)
	{
		n = double_quote - &export->str[i];
		write(out, &export->str[i], n);
		write(out, "\\", 1);
		i += n;
		double_quote = ft_strchr(&export->str[i + 1], '"');
	}
	ft_putstr_fd(&export->str[i], out);
}

void	print_export(t_shnode *export, int out)
{
	while (export)
	{
		ft_putstr_fd("declare -x ", out);
		ft_putstr_fd(export->name, out);
		if (export->str)
		{
			ft_putstr_fd("=\"", out);
			escape_double_quotes(export, out);
			ft_putstr_fd("\"", out);
		}
		ft_putstr_fd("\n", out);
		export = export->next;
	}
}
