/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:00:15 by youskim           #+#    #+#             */
/*   Updated: 2022/07/03 17:00:17 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_pwd(t_root *top)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (EXIT_FAILURE);
	ft_putendl_fd(path, top->out_fd);
	return (EXIT_SUCCESS);
}

void	pwd_process(t_root *top)
{
	int		fd[2];

	pipe(fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		if (bt_pwd(top) != 0)
			exit(1);
		exit(0);
	}
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}
