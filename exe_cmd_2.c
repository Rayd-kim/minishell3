/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:53:27 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 14:53:28 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_process_fd(t_root *top, int *fd)
{
	if ((top->out_fd == 1 && pipe_check(top) == 0) || \
		(pipe_heredoc_check(top) == 0 && top->out_fd == 1))
	{
		dup2(fd[1], 1);
		dup2(top->in_fd, 0);
	}
	else
	{
		dup2(top->in_fd, 0);
		dup2(top->out_fd, 1);
		close (fd[1]);
	}
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[0]);
}

char	*make_exe_path(char *env_path, char *cmd)
{
	char	*temp;
	char	*path;

	path = ft_strjoin (env_path, "/");
	temp = path;
	path = ft_strjoin (temp, cmd);
	free(temp);
	return (path);
}

void	check_cmd(char *str, t_root *top)
{
	char	**split;
	char	*path;
	char	*copy;
	int		i;

	i = 0;
	copy = ft_strdup(ft_strchr(str, '/'));
	split = ft_split(copy, ':');
	free (copy);
	while (split[i] != NULL && check_slash(top->left->right->cmd) == 0 \
			&& ft_strncmp(top->left->right->cmd, "\0", 1) != 0)
	{
		path = make_exe_path (split[i], top->left->right->cmd);
		if (access_check(path) == 0)
		{
			do_execve (path, top);
			split_free(split);
			free(path);
			return ;
		}
		free(path);
		i++;
	}
	split_free(split);
	do_execve (top->left->right->cmd, top);
}
