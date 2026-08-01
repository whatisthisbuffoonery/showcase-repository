/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:45 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:45 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

sig_atomic_t	g_signo;

int	shell_exit(t_env *env)
{
	ft_putstr("exit\n");
	rl_clear_history();
	clean_shnode_dup(&env->env);
	clean_shnode(&env->export);
	clean_ast(env->ast);
	free(env->pwd);
	free(env->oldpwd);
	return (env->last);
}

void	init(t_env *env, char **e, t_tok **tok)
{
	signal_init();
	*tok = NULL;
	env_init(env, e);
	env->ast = NULL;
	env->last = 0;
	env->do_not_subshell = 0;
	env->duped_fd[0] = 0;
	env->duped_fd[1] = 0;
	ft_memset(env->last_string, 0, 4);
	env->last_string[0] = '0';
}

//need to update last in execution
int	execute_buffer(t_env *env, t_tok **tok, char **buf)
{
	free(*buf);
	*buf = NULL;
	errno = 0;
	make_word(*tok);
	env->ast = parse(tok);
	if (g_signo)
		update_last(env, g_signo);
	else if (env->ast)
		update_last(env, do_list(env->ast, env));
	else
		update_last(env, 1 + !errno);
	clean_ast(env->ast);
	env->ast = NULL;
	if (g_signo && env->last == g_signo)
		replace_nl();
	return (env->last);
}

//updating last for tok init causes $? to always show 0
int	loop(char **e)
{
	char	*buf;
	t_env	env;
	t_tok	*tok;

	init(&env, e, &tok);
	while (1)
	{
		buf = readline("I am a shell% ");
		if (!buf)
			return (shell_exit(&env));
		if (buf[0])
			add_history(buf);
		if (!buf_check(buf, &env))
		{
			env.last = tok_init(buf, &tok);
			if (!env.last)
				execute_buffer(&env, &tok, &buf);
			else
				update_last(&env, env.last);
		}
		free(buf);
		clean_tok(&tok);
		g_signo = 0;
	}
	return (env.last);
}
