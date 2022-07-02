/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:18 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 23:39:20 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(t_root *top, int fd)
{
	int		len;
	char	buffer[20];

	len = read (top->in_fd, buffer, 20);
	while (len != 0)
	{
		write (fd, buffer, ft_strlen(buffer));
		len = read (top->in_fd, buffer, 20);
	}
}

int	check_heredoc(char *name, t_root *top)
{
	char	*temp;
	int		fd[2];

	g_vari.flag = 1;
	pipe(fd);
	if (top->in_fd != 0)
		read_heredoc(top, fd[1]);
	temp = readline (">");
	if (temp != NULL)
	{
		while (ft_strncmp (temp, name, ft_strlen(temp)) != 0 \
			|| ft_strncmp (temp, name, ft_strlen(name)) != 0)
		{
			write (fd[1], temp, ft_strlen(temp));
			write (fd[1], "\n", 1);
			free (temp);
			temp = readline (">");
			if (temp == NULL)
				break ;
		}
	}
	if (temp != NULL)
		free (temp);
	close (fd[1]);
	return (fd[0]);
}

void	set_redirection(t_root *top, int fd, int in_or_out, int *check)
{
	if (fd < 0)
	{
		*check = 1;
		return ;
	}
	if (in_or_out == 0)
	{
		if (top->in_fd != 0 && top->in_fd != top->here_doc)
			close (top->in_fd);
		top->in_fd = fd;
	}
	else
	{
		if (top->out_fd != 1)
			close (top->out_fd);
		top->out_fd = fd;
	}
}

int	do_heredoc_first(t_root *root)
{
	t_root	*top;
	t_node	*node;

	top = root;
	while (top != NULL)
	{
		node = top->left->left;
		while (node != NULL)
		{
			if (ft_strncmp (node->cmd, "<<", 2) == 0)
			{
				top->in_fd = check_heredoc(node->redi, top);
				if (top->in_fd < 0)
					return (1);
				top->here_doc = 1;
			}
			if (g_vari.status == 130)
				return (1);
			node = node->left;
		}
		top = top->right;
	}
	return (0);
}

int	do_redirection(t_root *top)
{
	t_node	*temp;
	int		check;

	if (top->here_doc != 0)
		top->here_doc = top->in_fd;
	check = 0;
	temp = top->left->left;
	while (temp != NULL)
	{
		if (ft_strncmp (temp->cmd, ">>", 3) == 0)
			set_redirection(top, open_redirection(temp->redi, 2), 1, &check);
		else if (ft_strncmp (temp->cmd, "<", 2) == 0)
			set_redirection(top, open_file (temp->redi), 0, &check);
		else if (ft_strncmp (temp->cmd, "<<", 3) == 0)
			set_redirection(top, top->here_doc, 0, &check);
		else if (ft_strncmp (temp->cmd, ">", 2) == 0)
			set_redirection(top, open_redirection(temp->redi, 1), 1, &check);
		if (check != 0)
			return (1);
		temp = temp->left;
	}
	return (0);
}
