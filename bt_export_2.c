/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilim <ilim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:07:20 by ilim              #+#    #+#             */
/*   Updated: 2022/07/02 16:07:51 by ilim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *args, t_list *env_list)
{
	t_list	*temp;

	temp = env_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = make_list();
	temp->next->str = ft_strdup(args);
}

int	bt_export(char **args, t_list *env_list, t_root *top)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (args[1] == NULL)
	{
		null_args(env_list);
		return (EXIT_SUCCESS);
	}
	while (args[i] != NULL)
	{
		if (!check_alpha(args[i], &ret) && \
			(top->in_fd == 0 && top->right == NULL))
		{
			if (check_dup(args[i], env_list))
				add_env(args[i], env_list);
		}
		i++;
	}
	return (ret);
}

void	export_process_no_arg(t_root *top, t_list *env)
{
	int		fd[2];

	pipe(fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		bt_export(top->left->right->arg, env, top);
		exit(0);
	}
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}

void	export_process_arg(t_root *top, t_list *env)
{
	int		fd[2];

	pipe(fd);
	g_vari.status = bt_export(top->left->right->arg, env, top);
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}

void	export_process(t_root *top, t_list *env)
{
	if (top->left->right->arg[1] == NULL)
		export_process_no_arg(top, env);
	else
		export_process_arg(top, env);
}
