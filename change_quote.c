/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:12:44 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 16:12:45 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote(char *str, int type)
{
	char	*ret;
	int		i;
	int		k;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (ret == 0)
		exit (1);
	i = 0;
	k = 0;
	while (str[i] != '\0' && k < ((int)ft_strlen(str) - 1))
	{
		if (type == 1 && str[i] != '\'')
		{
			ret[k] = str[i];
			k++;
		}
		else if (type == 2 && str[i] != '\"')
		{
			ret[k] = str[i];
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	return (ret);
}

char	*change_quote_2(char *str, char *temp, char *free_temp)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			ret = remove_quote (temp, 2);
			if (ret != temp && free_temp != NULL)
				free(free_temp);
			return (ret);
		}
		else if (str[i] == '\'')
			return (remove_quote (temp, 1));
		i++;
	}
	return (temp);
}

char	*change_quote(char *str, t_list *env)
{
	char	*temp;
	char	*free_temp;

	free_temp = NULL;
	temp = check_env(str, env);
	if (temp != str)
	{
		while (1)
		{
			free_temp = temp;
			temp = check_env(temp, env);
			if (free_temp == temp)
				break ;
			free(free_temp);
		}
	}
	return (change_quote_2(str, temp, free_temp));
}
