/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilim <ilim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:01:11 by ilim              #+#    #+#             */
/*   Updated: 2022/07/02 16:07:47 by ilim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_export_msg(char *args)
{
	ft_putstr_fd("Minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

int	check_dup(char *args, t_list *env_list)
{
	char	*ptr;
	int		idx;
	int		i;
	t_list	*tmp;

	tmp = env_list;
	ptr = ft_strchr(args, '=');
	if (ptr == NULL)
		return (0);
	idx = (ptr - args);
	while (tmp && ptr)
	{
		i = 0;
		while (args[i] == tmp->str[i])
		{
			if (i++ == idx)
			{
				free(tmp->str);
				tmp->str = ft_strdup(args);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_valid(char *args, int i, int flag)
{
	while (args[i])
	{
		if (ft_isalpha(args[0]) && args[i] != '\0')
		{
			if ((args[i] >= 48 && args[i] <= 57) || ft_isalpha(args[i]))
				;
			else if (args[i] == '=')
			{
				if (args[i + 1] == '\0' || i == 0)
				{
					i++;
					continue ;
				}
			}
		}
		else
			flag = 1;
		if (flag)
		{
			prt_export_msg(args);
			break ;
		}	
		i++;
	}
	return (flag);
}

int	check_alpha(char *args, int *ret)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (args[0] == '\0')
	{
		prt_export_msg(args);
		*ret = 1;
		return (EXIT_FAILURE);
	}
	flag = check_valid(args, i, flag);
	if (flag)
	{
		*ret = 1;
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}

void	null_args(t_list *env_list)
{
	int		i;

	while (env_list)
	{
		i = 0;
		printf("declare -x ");
		while (env_list->str[i])
		{
			printf("%c", env_list->str[i]);
			if (env_list->str[i] == '=')
				break ;
			i++;
		}
		i++;
		printf("%c", '\"');
		while (env_list->str[i])
			printf("%c", env_list->str[i++]);
		printf("%c\n", '\"');
		env_list = env_list->next;
	}
}
