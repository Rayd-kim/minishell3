/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:07:43 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 16:07:44 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	env_len(char *path)
{
	int	i;

	i = 0;
	while (path[i] != ' ' && path[i] != '\"' && path[i] != '\0' \
			&& path[i] != '\'' && path[i] != '?' && path[i] != '$')
		i++;
	return (i);
}

char	*check_env(char *str, t_list *env)
{
	int		quote_single;
	int		quote_double;
	int		i;

	i = 0;
	quote_single = 0;
	quote_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote_double % 2 == 0)
			quote_single++;
		if (str[i] == '\"')
			quote_double++;
		else if (str[i] == '$' && quote_single % 2 == 0)
			return (check_env_vari(str, env));
		else if (str[i] == '$' && quote_double % 2 != 0 \
				&& quote_single % 2 == 0)
			return (check_env_vari(str, env));
		i++;
	}
	return (str);
}
