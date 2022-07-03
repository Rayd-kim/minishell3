/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:37 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 23:06:37 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *str, t_root *top, t_list *env)
{
	if (ft_strncmp(str, "echo", ft_strlen (str)) == 0 && \
		ft_strncmp(str, "echo", 4) == 0)
		echo_process(top);
	else if (ft_strncmp(str, "cd", ft_strlen (str)) == 0 && \
		ft_strncmp(str, "cd", 2) == 0)
		cd_process(top);
	else if (ft_strncmp(str, "env", ft_strlen (str)) == 0 && \
		ft_strncmp(str, "env", 3) == 0)
		env_process(top, env);
	else if (ft_strncmp(str, "unset", ft_strlen (str)) == 0 && \
		ft_strncmp(str, "unset", 5) == 0)
		unset_process(top, env);
	else if (ft_strncmp(str, "export", ft_strlen (str)) == 0 && \
		ft_strncmp(str, "export", 6) == 0)
		export_process(top, env);
	else if (ft_strncmp(str, "pwd", ft_strlen (str)) == 0 && \
		ft_strncmp(str, "pwd", 3) == 0)
		pwd_process(top);
	else if (ft_strncmp(str, "exit", ft_strlen (str)) == 0 && \
		ft_strncmp(str, "exit", 3) == 0)
		exit_process(top);
	else
		return (1);
	return (0);
}

void	do_cmd(t_root *top, t_list *env)
{
	t_list	*list;

	list = env;
	while (list != NULL && top->left->right != NULL)
	{
		if (top->left->right->cmd == NULL)
		{
			g_vari.status = 0;
			return ;
		}
		else if (check_builtin(top->left->right->cmd, top, env) == 0)
			return ;
		else if (ft_strncmp(list->str, "PATH=", 5) == 0)
		{
			check_cmd (list->str, top);
			return ;
		}
		list = list->next;
	}
	if (top->left->right == NULL)
		do_execve_null (top);
	else
		do_execve (top->left->right->cmd, top);
}

void	after_heredoc(t_root *start, t_list *env)
{
	t_root	*root_temp;
	int		fd[2];

	root_temp = start;
	while (root_temp != NULL)
	{
		if (root_temp->left != NULL)
		{
			if (do_redirection(root_temp) == 0 && g_vari.status != 130)
				do_cmd(root_temp, env);
			else
			{
				if (root_temp->right != NULL && pipe_check(root_temp) == 0)
				{
					pipe(fd);
					close (fd[1]);
					root_temp->right->in_fd = fd[0];
					if (root_temp->in_fd != 0)
						close (root_temp->in_fd);
				}
			}
		}
			root_temp = root_temp->right;
	}
}

void	exe_cmd(t_root *start, t_list *env)
{
	if (do_heredoc_first(start) != 0)
		return ;
	after_heredoc(start, env);
	pid_check(start);
}
