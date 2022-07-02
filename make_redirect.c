/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:55 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 23:29:39 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(char *str)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			s++;
		else if (str[i] == '\"')
			d++;
		else if (ft_strncmp (&str[i], ">>", 2) == 0 && s % 2 == 0 && d % 2 == 0)
			return (2);
		else if (ft_strncmp (&str[i], "<<", 2) == 0 && s % 2 == 0 && d % 2 == 0)
			return (2);
		else if (ft_strncmp (&str[i], ">", 1) == 0 && s % 2 == 0 && d % 2 == 0)
			return (1);
		else if (ft_strncmp (&str[i], "<", 1) == 0 && s % 2 == 0 && d % 2 == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*cmd_redirection(char *str)
{
	char	*ret;
	int		len;
	int		i;
	int		k;

	len = check_redirection(str);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		exit (1);
	i = 0;
	k = 0;
	while (k < len)
	{
		if (str[i] == '>' || str[i] == '<')
		{
			ret[k] = str[i];
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	return (ret);
}

char	*arg_redirection_2(char *str, t_list *env)
{
	char	*change;
	char	*ret;

	change = change_quote(str, env);
	ret = ft_strdup(change);
	if (change != str)
		free(change);
	return (ret);
}

char	*arg_redirection(char *str, char **cut, int *index, t_root *root)
{
	int		i;

	i = 0;
	while (str[i] != '>' && str[i] != '<')
		i++;
	if (str[i + 1] == '\0')
	{
		*index = *index + 1;
		return (arg_redirection_2(cut[*index], root->env));
	}
	else if (str[i + 1] == '>' || str[i + 1] == '<')
	{
		if (str[i + 2] == '\0')
		{
			*index = *index + 1;
			return (arg_redirection_2(cut[*index], root->env));
		}
		else
			return (arg_redirection_2(&str[i + 2], root->env));
	}
	else
		return (arg_redirection_2(&str[i + 1], root->env));
}

void	make_redirection(char *str, t_root	*root, char **cut, int *index)
{
	t_node	*temp;
	t_node	*redirect;

	redirect = (t_node *)malloc(sizeof(t_node));
	if (redirect == 0)
		exit(1);
	ft_memset (redirect, 0, sizeof(t_node));
	temp = root->left;
	while (temp->left != NULL)
		temp = temp->left;
	redirect->cmd = cmd_redirection (str);
	redirect->redi = arg_redirection (str, cut, index, root);
	temp->left = redirect;
}
