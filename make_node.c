/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 23:29:57 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_cmd(char *cut, t_node *start, t_list *env)
{
	t_node	*cmd;
	int		i;
	char	*str;

	i = 0;
	cmd = start->right;
	str = change_quote(cut, env);
	if (cmd->cmd == NULL)
	{
		cmd->cmd = ft_strdup(str);
		cmd->arg[0] = ft_strdup(str);
	}
	else
	{
		while (cmd->arg[i] != NULL)
			i++;
		cmd->arg[i] = ft_strdup(str);
	}
	if (str != cut)
		free (str);
}

void	set_cmd_arg(char **cut, t_node *node)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (cut[i])
	{
		if (check_redirection(cut[i]) == 0)
			len++;
		i++;
	}
	node->right = (t_node *)malloc(sizeof(t_node));
	if (node->right == 0)
		exit(1);
	ft_memset(node->right, 0, sizeof(t_node));
	node->right->arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (node->right->arg == 0)
		exit (1);
	ft_memset(node->right->arg, 0, sizeof(char *) * (len + 1));
}

void	make_node(char *split, t_root *start, t_list *env)
{
	char	**cut;
	int		i;

	cut = ft_split(split, (char)255);
	i = 0;
	set_cmd_arg(cut, start->left);
	while (cut[i] != NULL)
	{
		if (check_redirection(cut[i]) != 0)
			make_redirection (cut[i], start, cut, &i);
		else
			make_cmd (cut[i], start->left, env);
		i++;
	}
	split_free (cut);
}

t_root	*make_root(int root_in, int root_out, t_list *env)
{
	t_root	*ret;

	ret = (t_root *)malloc(sizeof(t_root));
	if (ret == 0)
		exit (1);
	ft_memset (ret, 0, sizeof(t_root));
	ret->in_fd = root_in;
	ret->out_fd = root_out;
	ret->env = env;
	return (ret);
}

t_root	*make_cmd_node(t_root *start, t_list *env)
{
	t_root	*temp;
	t_node	*cmd;
	t_root	*pipe;

	temp = start;
	if (temp->left != NULL)
	{
		pipe = make_root (0, 1, env);
		while (temp->right != NULL)
			temp = temp->right;
		temp->right = pipe;
		temp = temp->right;
	}
	cmd = (t_node *)malloc(sizeof(t_node));
	if (cmd == 0)
		exit (1);
	ft_memset (cmd, 0, sizeof(t_node));
	temp->left = cmd;
	return (temp);
}
