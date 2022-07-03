/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo_and_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:51:07 by youskim           #+#    #+#             */
/*   Updated: 2022/07/01 16:51:08 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char **args)
{
	int	i;

	if (args[1][0] == '-')
	{
		i = 1;
		while (args[1][i])
		{
			if (args[1][i] == 'n')
				i++;
			else
				return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	check_nn(char *args)
{
	int	i;

	i = 1;
	while (args[i] != '\0')
	{
		if (args[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	check_multi_n(char **args, int *opt)
{
	int	i;

	i = 1;
	if (args[i][0] == '-' && check_nn(args[i]) == 0)
		*opt = 1;
	while (args[i][0] == '-' && check_nn(args[i]) == 0)
	{
		*opt += 1;
		i++;
	}
}

void	bt_echo(char **args, t_root *top)
{
	int		opt;

	opt = 0;
	if (args[1] == NULL)
	{
		ft_putchar_fd('\n', top->out_fd);
		return ;
	}
	if (!check_n(args))
		check_multi_n(args, &opt);
	else
		opt = 1;
	args += opt;
	while (*args != NULL)
	{
		ft_putstr_fd(*args, top->out_fd);
		if (*(args + 1) != NULL)
			ft_putchar_fd(' ', top->out_fd);
		++args;
	}
	if (opt == 1)
		ft_putchar_fd('\n', top->out_fd);
}

void	echo_process(t_root *top)
{
	int		fd[2];

	pipe(fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		bt_echo(top->left->right->arg, top);
		exit(0);
	}
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}
