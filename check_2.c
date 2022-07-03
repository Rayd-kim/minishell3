/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:04:57 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 14:04:58 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str, char **split, char *temp)
{
	int	single_q;
	int	double_q;
	int	i;

	single_q = 0;
	double_q = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && double_q % 2 == 0)
			single_q++;
		else if (str[i] == '\"' && single_q % 2 == 0)
			double_q++;
		i++;
	}
	if (single_q % 2 == 0 && double_q % 2 == 0)
		return (0);
	else
	{
		split_free (split);
		free (temp);
		write (2, "Unclosed quotes\n", 16);
		return (1);
	}
}

int	check_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_pipe_close(char *str)
{
	int	i;
	int	arg;

	i = 0;
	arg = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && arg == 0)
			break ;
		else if (str[i] == '|')
			arg = 0;
		else if (str[i] != ' ')
			arg++;
		i++;
	}
	if (str[i] == '\0' && i == 0)
		return (0);
	else if (arg == 0)
	{
		write (2, "Unclosed pipe\n", 14);
		free (str);
		return (1);
	}
	return (0);
}

void	check_redirection_close_2(char *str, int *i, int *arg)
{
	int	redi;

	redi = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '>' && str[*i + 1] == '<')
			break ;
		else if (str[*i] == '<' && str[*i + 1] == '>')
			break ;
		else if (redi > 2)
			break ;
		else if ((str[*i] == '>' && redi <= 2) || (str[*i] == '<' && redi <= 2))
		{
			redi++;
			*arg = 0;
		}
		else if (str[*i] != ' ')
		{
			redi = 0;
			*arg += 1;
		}
		*i += 1;
	}
}

int	check_redirection_close(char *str, char **split, char *temp)
{
	int	i;
	int	arg;

	arg = 0;
	i = 0;
	check_redirection_close_2(str, &i, &arg);
	if (str[i] != '\0' || arg == 0)
	{
		write (2, "Redirection error\n", 18);
		split_free (split);
		free (temp);
		return (1);
	}
	return (0);
}
