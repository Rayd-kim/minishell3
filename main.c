/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:46 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 23:59:45 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vari	g_vari;

void	pid_check(t_root *start)
{
	pid_t	now_pid;
	int		check;
	t_root	*temp;

	now_pid = 0;
	temp = start;
	while (temp->right != NULL)
		temp = temp->right;
	while (1)
	{
		now_pid = waitpid(0, &check, 0);
		if (now_pid == -1)
			break ;
		if (now_pid == temp->pid)
			g_vari.status = check >> 8;
	}
}

int	do_minishell(t_root *start, t_list *env, char *temp)
{
	char	**split;
	int		i;

	add_history (temp);
	if (check_pipe_close(temp) != 0)
		return (1);
	change_pipe (temp);
	split = ft_split (temp, (char)254);
	if (split == NULL)
		exit (1);
	i = -1;
	while (split[++i] != NULL)
	{
		if (check_quote(split[i], split, temp) != 0 \
			|| check_redirection_close(split[i], split, temp) != 0)
			return (1);
		change_space(split[i]);
		make_node(split[i], make_cmd_node((start), env), env);
	}
	split_free (split);
	free (temp);
	return (0);
}

int	show_prompt(t_root *start, t_list *env)
{
	char	*temp;

	temp = readline("minishell >>");
	if (temp != NULL && check_whitespace(temp) == 0)
	{
		if (do_minishell(start, env, temp) == 1)
			return (1);
	}
	else if (temp != NULL && check_whitespace(temp) != 0)
	{
		free(temp);
		return (1);
	}
	else if (temp == NULL)
	{
		printf("\x1b[1A\033[12C exit\n");
		exit(0);
	}
	return (0);
}

void	set_flag(void)
{
	if (g_vari.flag > 1 && g_vari.status == 130)
	{
		g_vari.status = 1;
		dup2 (g_vari.flag, 0);
		g_vari.flag = 2;
	}
	else if (g_vari.flag == 2)
		g_vari.flag = 2;
	else
		g_vari.flag = 0;
}

int	main(int arg, char *argv[], char **envp)
{
	t_root	*start;
	t_list	*env;

	if (arg > 1 || ft_strncmp (argv[0], "./minishell", ft_strlen(argv[0])) != 0)
		exit (1);
	setup_term();
	ft_memset (&g_vari, 0, sizeof(t_vari));
	env = make_env (envp);
	while (1)
	{
		set_signal(SIGUSR1);
		start = make_root (0, 1, env);
		if (show_prompt (start, env) == 0)
		{
			if (g_vari.status == 130)
				g_vari.status = 0;
			exe_cmd (start, env);
		}
		reset_root(start);
		set_flag();
	}
	return (0);
}
