/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:10:54 by youskim           #+#    #+#             */
/*   Updated: 2022/07/01 15:10:55 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(t_root *top)
{
	if (top->right != NULL)
	{
		if (top->right->in_fd == 0)
			return (0);
	}
	return (1);
}

int	pipe_heredoc_check(t_root *top)
{
	if (top->right != NULL)
		if (top->right->here_doc != 0)
			return (0);
	return (1);
}

int	check_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	access_check(char *path)
{
	int	fd;

	fd = open (path, O_RDONLY);
	if (fd != -1)
		return (0);
	else
	{
		close (fd);
		return (1);
	}
}
