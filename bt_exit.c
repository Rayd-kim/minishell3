/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:57:13 by youskim           #+#    #+#             */
/*   Updated: 2022/07/01 16:57:14 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	result_value(const char *str, int index, int sign, int *check)
{
	unsigned long long int	result;

	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (result > 9223372036854775807 && sign == 1)
	{
		*check = 1;
		return (-1);
	}
	else if (result - 1 > 9223372036854775807 && sign == -1)
	{
		*check = 1;
		return (0);
	}
	else
		return (result * sign);
}

int	ft_exit_atoi(const char *str, int *check)
{
	int	i;
	int	sign;
	int	result;
	int	pm_num;

	i = 0;
	pm_num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		pm_num++;
		i++;
	}
	if (pm_num > 1 && ft_strlen(str) > 19)
	{
		*check = 1;
		return (0);
	}
	result = result_value(str, i, sign, check);
	return (result);
}

int	custom_isdigit(char *args)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	ft_exit_atoi(args, &check);
	if (check == 1)
		return (EXIT_FAILURE);
	if (args[i] == '\0')
		return (EXIT_FAILURE);
	while (args[i])
	{
		if ((args[i] >= '0' && args[i] <= '9') || \
			args[i] == '-' || args[i] == '+')
			i++;
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	bt_exit(char **args, int *end_check)
{
	unsigned char	negative;

	if (args[1] == NULL)
	{
		*end_check = 1;
		return (EXIT_SUCCESS);
	}
	if (custom_isdigit(args[1]))
	{
		write_error("Minishell: exit: ");
		write_error(args[1]);
		write_error(": numeric argument required\n");
		*end_check = 1;
		return (255);
	}
	else if (args[2] != NULL)
	{
		write_error("Minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	negative = ft_atoi(args[1]);
	*end_check = 1;
	return (negative);
}

void	exit_process(t_root *top)
{
	int		fd[2];
	int		end_check;
	int		end_value;

	end_check = 0;
	pipe(fd);
	if (top->in_fd == 0 && top->right == NULL)
		printf("exit\n");
	end_value = bt_exit(top->left->right->arg, &end_check);
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	else
		close (fd[0]);
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
	if (top->in_fd == 0 && top->right == NULL && end_check == 1)
		exit (end_value);
	g_vari.status = end_value;
}
