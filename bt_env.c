/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env_and_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilim <ilim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:54:11 by youskim           #+#    #+#             */
/*   Updated: 2022/07/03 18:27:57 by ilim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (1)
	{
		if (temp != NULL)
			printf("%s\n", temp->str);
		else
			break ;
		temp = temp->next;
	}
}

void	env_process(t_root *top, t_list *env)
{
	int		fd[2];

	pipe(fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		prt_env(env);
		exit(0);
	}
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}
