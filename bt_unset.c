/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:58:44 by youskim           #+#    #+#             */
/*   Updated: 2022/07/03 18:58:45 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(t_list *env_list, char *args)
{
	t_list	*list;
	t_list	*prev;
	char	*temp;

	temp = ft_strjoin(args, "=");
	list = env_list;
	prev = NULL;
	while (list != NULL)
	{
		if (!ft_strncmp(temp, list->str, ft_strlen(temp)))
		{
			if (prev != NULL)
				prev->next = list->next;
			free(list->str);
			free (list);
			break ;
		}
		else
		{
			prev = list;
			list = list->next;
		}
	}
	free(temp);
}

int	check_num_alpha(char *args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i] == '=')
			return (1);
		else if (!ft_isalpha(args[i]) && !ft_isdigit(args[i]))
			return (1);
		i++;
	}
	return (0);
}

void	bt_unset(char **args, t_list *env_list, t_root *top)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (args[i] == NULL)
		return ;
	while (args[++i] != NULL)
	{
		if (!ft_isalpha(args[i][0]) || ft_strchr(args[i], '=') || \
			check_num_alpha(args[i]))
		{
			ft_putstr_fd("Minihsel: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("':  not a valid identifier", STDERR_FILENO);
			flag = 1;
			g_vari.status = 1;
		}
		else if (top->in_fd == 0 && top->right == NULL)
		{
			delete_env(env_list, args[i]);
			if (flag != 1)
				g_vari.status = 0;
		}
	}
}

void	unset_process(t_root *top, t_list *env)
{
	int		fd[2];

	pipe(fd);
	if (top->left->right->arg != NULL)
		bt_unset(top->left->right->arg, env, top);
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	else
		close (fd[0]);
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}
