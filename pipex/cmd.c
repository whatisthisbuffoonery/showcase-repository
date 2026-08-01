/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:18:22 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/07 17:34:01 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

//EACCES is split between:
//dirs not having read access
//and the actual X_OK failure code
//and we never check the other valid binaries after finding the first one
int	cmd_name_help(char ***cmd_src, char *ret, char **env, int len)
{
	int		i;
	char	*check_x;
	char	*cmd;
	int		(*f_err)(int, char *);

	i = 0;
	errno = 0;
	cmd = (*cmd_src)[0];
	while (env && env[i])
	{
		ft_strlcpy(ret, env[i], len);
		ft_strlcat(ret, "/", len);
		ft_strlcat(ret, cmd, len);
		if (!access(ret, F_OK))
			break ;
		i ++;
	}
	check_x = ret;
	if (!env || !env[i])
		check_x = cmd;
	f_err = oops_err;
	if (!ret)
		f_err = cmd_err;
	return (f_err(access(check_x, X_OK), cmd));
}

//one for null terminator, one for extra '/'
int	max_len(char **ret, char **cmd, char **env)
{
	int	i;
	int	len;
	int	next;

	i = 0;
	len = 0;
	while (env && env[i])
	{
		next = ft_strlen(env[i]);
		if (next > len)
			len = next;
		i ++;
	}
	len += ft_strlen(cmd[0]) + 1 + 1;
	if (env)
		*ret = malloc(len * sizeof(char));
	return (len);
}

int	cmd_name(char ***cmd, char **env)
{
	int		len;
	char	*ret;

	errno = 0;
	ret = NULL;
	len = max_len(&ret, *cmd, env);
	if (env && !ret)
	{
		oops_err(-1, (*cmd)[0]);
		return (cmd_cleanup(cmd));
	}
	if (cmd_name_help(cmd, ret, env, len))
	{
		free(ret);
		return (cmd_cleanup(cmd));
	}
	if (ret)
	{
		free((*cmd)[0]);
		(*cmd)[0] = ret;
	}
	return (0);
}

int	find_path(char **e, char **path)
{
	int				i;
	unsigned int	len;
	char			*prefix;

	i = 0;
	prefix = "PATH=";
	len = ft_strlen(prefix);
	while (e && e[i])
	{
		if (!ft_strncmp(e[i], prefix, len) && ft_strlen(e[i]) > len)
		{
			*path = &e[i][len];
			return (0);
		}
		i ++;
	}
	if (e)
		errno = ENOENT;
	return ((e != NULL));
}

int	cmd_init(char **v, int *i, char ***cmd, char **e)
{
	char	**env;
	char	*path;
	int		flag;

	flag = 0;
	path = NULL;
	env = NULL;
	errno = 0;
	if (!cmd_strchr(v[*i]) && find_path(e, &path))
		return (oops_err(-1, v[*i]));
	if (path)
	{
		env = ft_split(path, ':');
		if (!env)
			return (oops_err(-1, v[*i]));
	}
	*cmd = parsed_argsplit(v[*i]);
	if (!*cmd)
		one_off_err(v[*i]);
	if (!*cmd || cmd_name(cmd, env))
		flag = 1;
	cmd_cleanup(&env);
	return (flag);
}
