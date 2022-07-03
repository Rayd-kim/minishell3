/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:46:14 by youskim           #+#    #+#             */
/*   Updated: 2022/07/01 16:46:15 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_left(t_node *top)
{
	t_node	*node;
	t_node	*free_node;

	node = top;
	if (node->right != NULL)
	{
		if (node->right->cmd != NULL)
			free (node->right->cmd);
		split_free (node->right->arg);
		free (node->right);
	}
	free_node = node;
	node = node->left;
	free (free_node);
	while (node != NULL)
	{
		if (node->cmd != NULL)
			free (node->cmd);
		if (node->redi != NULL)
			free (node->redi);
		free_node = node;
		node = node->left;
		free (free_node);
	}
}

void	reset_root(t_root *start)
{
	t_root	*root;
	t_root	*free_root;

	root = start;
	while (root != NULL)
	{
		if (root->left != NULL)
			free_left (root->left);
		if (root->in_fd != 0)
			close (root->in_fd);
		if (root->out_fd != 1)
			close (root->out_fd);
		free_root = root;
		root = root->right;
		free (free_root);
	}
}

void	split_free(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free (split);
}

void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
