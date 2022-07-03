/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:47:49 by youskim           #+#    #+#             */
/*   Updated: 2022/07/01 16:47:50 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_execve_null(t_root *top)
{
	int		fd[2];

	pipe (fd);
	top->pid = fork();
	set_signal(SIGUSR2);
	if (top->pid == 0)
		set_process_fd(top, fd);
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	else
		close (fd[0]);
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}

char	**make_exe_env(t_list *env)
{
	t_list	*list;
	char	**ret;
	int		len;
	int		i;

	len = 0;
	i = 0;
	list = env;
	while (list != NULL)
	{
		len++;
		list = list->next;
	}
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (ret == 0)
		exit (1);
	list = env;
	while (i < len)
	{
		ret[i] = list->str;
		i++;
		list = list->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	do_execve(char *path, t_root *top)
{
	int		fd[2];

	pipe(fd);
	top->pid = fork();
	set_signal(SIGUSR2);
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		if (execve(path, top->left->right->arg, make_exe_env(top->env)) == -1)
			error_stdin (path, check_slash(top->left->right->cmd));
	}
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	else
		close (fd[0]);
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}
