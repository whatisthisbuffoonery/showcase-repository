/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 export.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: achew <achew@student.42singapore.sg>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/04/22 01:12:45 by achew			   #+#	  #+#			  */
/*	 Updated: 2026/04/22 01:12:53 by achew			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "h_minishell.h"

static int	env_set(t_shnode *exp_node, char *name, char *val, t_env *env)
{
	t_shnode	*existing;
	t_shnode	*env_node;

	existing = find_env(name, env->env);
	if (existing && val)
		existing->str = exp_node->str;
	else if (val)
	{
		env_node = shnode_dup(exp_node);
		if (!env_node)
			return (1);
		shnode_append(&env->env, env_node);
	}
	return (0);
}

static int	export_set(char *arg, char *name, char *val, t_env *env)
{
	t_shnode	*existing;
	t_shnode	*exp_node;

	existing = find_env(name, env->export);
	exp_node = existing;
	if (existing && val)
		update_val(val, existing);
	else if (!existing)
	{
		exp_node = env_init_node(arg);
		if (!exp_node)
			return (1);
		shnode_append(&env->export, exp_node);
	}
	return (env_set(exp_node, name, val, env));
}

static int	process_export_arg2(char *arg, int name_len, char *eq, t_env *env)
{
	char	*name;
	int		status;

	name = ft_calloc(name_len + 1, sizeof(char));
	if (!name)
		return (1);
	ft_strlcpy(name, arg, name_len + 1);
	if (invalid_var(name))
		status = invalid_identifier(name);
	else if (!eq)
		status = export_set(arg, name, NULL, env);
	else
		status = export_set(arg, name, eq + 1, env);
	free(name);
	return (status);
}

static int	process_export_arg(char *arg, t_env *env)
{
	char	*eq;
	int		name_len;

	if (!arg || arg[0] == '=')
		return (invalid_identifier(arg));
	eq = ft_strchr(arg, '=');
	if (eq)
		name_len = eq - arg;
	else
		name_len = ft_strlen(arg);
	return (process_export_arg2(arg, name_len, eq, env));
}

int	ft_export(int argc, char **argv, t_env *env, int out)
{
	int		i;
	int		status;

	if (argc < 2)
	{
		print_export(env->export, out);
		return (0);
	}
	status = 0;
	i = 1;
	while (i < argc)
	{
		status = process_export_arg(argv[i], env);
		i++;
	}
	return (status);
}
