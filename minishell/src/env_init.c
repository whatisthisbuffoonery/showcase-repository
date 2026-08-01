/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:23 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/18 22:03:02 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//bc i need "export a" to be displayed differently from "export a=" (a vs a="")
t_shnode	*env_init_node(char *e)
{
	t_shnode	*ret;
	int			i;

	ret = ft_calloc(1, sizeof(t_shnode));
	if (!ret)
		return (NULL);
	i = 0;
	while (e[i] && e[i] != '=')
		i ++;
	ret->name = ft_strndup(e, i);
	if (!ret->name)
		return (clean_one_shnode(ret));
	if (e[i])
	{
		ret->str = ft_strdup(&e[i + 1]);
		if (!ret->str)
			return (clean_one_shnode(ret));
	}
	else
		ret->str = NULL;
	return (ret);
}

//no recovery method
char	*grab_home(t_env *env)
{
	t_shnode	*tmp;

	tmp = find_env("HOME", env->env);
	if (!tmp)
		return (NULL);
	return (tmp->str);
}

void	pwd_init(t_env *env)
{
	t_shnode	*tmp;
	char		*tmpstr;

	tmp = find_env("PWD", env->env);
	if (tmp && tmp->str)
		env->pwd = ft_strdup(tmp->str);
	else
		env->pwd = getcwd(NULL, 0);
	tmp = find_env("OLDPWD", env->env);
	if (tmp && tmp->str)
		env->oldpwd = ft_strdup(tmp->str);
	else
	{
		tmpstr = grab_home(env);
		if (tmpstr)
			env->oldpwd = ft_strdup(tmpstr);
	}
	ft_err(-!env->pwd, "pwd init error");
	ft_err(-!env->oldpwd, "oldpwd init error");
}

//test program on null envp
void	env_init(t_env *dst, char **e)
{
	int			i;
	t_shnode	*iter;

	i = 0;
	ft_memset(dst, 0, sizeof(t_env));
	if (!e || !*e)
	{
		ft_putstr_fd("minishell: warning: null envp at init\n", 2);
		return ;
	}
	while (e[i])
	{
		iter = env_init_node(e[i]);
		if (!iter && ft_err((-!iter), "export node malloc"))
			break ;
		env_add(dst, iter, "env");
		env_add(dst, iter, "export");
		i ++;
	}
	update_shell_lvl(dst, 0);
	pwd_init(dst);
	env_import(dst);
}
