/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_pipex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:19:08 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 18:55:19 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_PIPEX_H
# define H_PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"
# include "get_next_line_bonus.h"
# include <sys/wait.h>
# include <errno.h>

void	cpid_add(pid_t *dst, pid_t src, int *index, char **v);
int		cpid_nuke(pid_t **cpid);
int		cpid_status(pid_t *cpid, char **v, int index);

int		pipex_arg(int c);
void	exec_wrap(char **src);

int		pfd_len(char **v);
int		heredoc_cond(char **v);
int		ffd_heredoc(char **v, int *i, int *pfd, pid_t **cpid);

int		ffd_start(char **v, int *i);
int		ffd_end(char *v, int heredoc_flag);

int		child_wait(pid_t cpid);
void	child_err(char **cmd, char **v, int **pfd, int *ffd);

int		pfd_grab(int i, char **v);
int		cmd_init(char **v, int *i, char ***cmd, char **e);
void	fork_handler(char **v, int *i, int *pfd_src, char **e);

int		cmd_strchr(char *v);

int		oops_err(int n, char *str);
int		cmd_err(int n, char *str);
int		err(int n, char *str);
int		one_off_err(char *str);

void	unset(int *fd);
void	fd_cleanup(int **pfd, int *ffd, char **v);
int		cmd_cleanup(char ***cmd);

#endif
