/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:09 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:09 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

t_shnode	*shnode_replace(char *name, char **src, char *builtin)
{
	t_shnode	*tmp;

	tmp = malloc(sizeof(t_shnode));
	if (tmp)
		tmp->name = ft_strdup(name);
	if (builtin_err(!tmp || !tmp->name, builtin, "could not replace node"))
	{
		if (tmp)
			free(tmp->name);
		free(tmp);
		free(*src);
		*src = NULL;
		return (NULL);
	}
	tmp->str = *src;
	return (tmp);
}

void	shnode_update(char *name, char *src, t_env *env)
{
	t_shnode	*tmp;
	char		*val;

	val = ft_strdup(src);
	tmp = find_env(name, env->export);
	if (builtin_err(!val, "cd", "could not update env lists"))
		return ;
	if (tmp)
	{
		free(tmp->str);
		tmp->str = val;
	}
	else
		env_add(env, shnode_replace(name, &val, "cd"), "export");
	tmp = find_env(name, env->env);
	if (tmp && val)
		tmp->str = val;
	else
		env_add(env, find_env(name, env->export), "env");
}

int	change_dir(char *dst, char *v, t_env *env)
{
	int	ret;

	ret = chdir(dst);
	if (!builtin_err(ret, "cd", v))
	{
		free(env->oldpwd);
		env->oldpwd = env->pwd;
		env->pwd = dst;
		pwd_trim(dst);
		shnode_update("OLDPWD", env->oldpwd, env);
		shnode_update("PWD", env->pwd, env);
	}
	else
		free(dst);
	return (ret);
}

char	*grab_v(char **v, t_env *env, int *status)
{
	char	*ret;

	ret = v[1];
	if (!ret || !ft_strcmp(ret, "~"))
		ret = grab_home(env);
	else if (!ft_strcmp(ret, "-"))
	{
		ret = find_env_str("OLDPWD", env, ft_strlen("OLDPWD"));
		if (!ret)
			ret = env->oldpwd;
	}
	*status = builtin_err(!ret, "cd", "HOME not set");
	return (ret);
}

//dont free v
int	cd(int argc, char **argv, t_env *env)
{
	char	*v;
	char	*dst;
	int		status;

	if (shell_assert(argc > 2, "too many arguments"))
		return (1);
	v = grab_v(argv, env, &status);
	if (!v || !v[0])
		return (status);
	if (!env->pwd)
		env->pwd = getcwd(NULL, 0);
	dst = NULL;
	if (env->pwd)
		dst = malloc(ft_strlen(v) + ft_strlen(env->pwd) + 1 + 1);
	status = shell_assert2(!dst, "cd", "malloc error");
	if (dst)
	{
		ft_strlcpy(dst, env->pwd, -1);
		status = new_pwd(dst, v);
		if (!status)
			status = change_dir(dst, v, env);
		else
			free(dst);
	}
	return (cd_exit(status, argv[1], env->pwd));
}
