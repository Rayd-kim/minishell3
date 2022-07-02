/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:07:40 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 16:07:42 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_env_vari(char *str, t_list *env, char *path)
{
	char	*free_temp;
	char	*join;
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != '$')
		i++;
	temp = ft_substr(str, 0, i);
	join = ft_strjoin(temp, (env->str + env_len(path) + 1));
	free(temp);
	free_temp = join;
	i += env_len(path) + 1;
	temp = ft_substr(str, i, ft_strlen(&str[i]));
	join = ft_strjoin(join, temp);
	free(free_temp);
	free(temp);
	return (join);
}

char	*set_env_empty(char *str, char *path)
{
	char	*free_temp;
	char	*join;
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != '$')
		i++;
	temp = ft_substr(str, 0, i);
	i += env_len(path) + 1;
	free_temp = ft_substr(str, i, ft_strlen(&str[i]));
	join = ft_strjoin(temp, free_temp);
	free(free_temp);
	free(temp);
	return (join);
}

char	*set_exit_status(char *str)
{
	char	*free_temp;
	char	*join;
	char	*temp;
	char	*itoa;
	int		i;

	i = 0;
	while (str[i] != '$')
		i++;
	temp = ft_substr(str, 0, i);
	free_temp = temp;
	itoa = ft_itoa(g_vari.status);
	temp = ft_strjoin (temp, itoa);
	free(itoa);
	free(free_temp);
	i += 2;
	free_temp = ft_substr(str, i, ft_strlen(&str[i]));
	join = ft_strjoin(temp, free_temp);
	free(free_temp);
	free(temp);
	return (join);
}

char	*check_env_vari(char *str, t_list *env)
{
	t_list	*temp;
	char	*path;

	path = ft_strchr(str, '$');
	temp = env;
	if (path != NULL)
	{
		path = path + 1;
		while (temp != NULL)
		{
			if (ft_strncmp(path, "?", 1) == 0)
				return (set_exit_status(str));
			else if (ft_strncmp(path, temp->str, env_len(path)) == 0 && \
					ft_strncmp(path, temp->str, path_len(temp->str)) == 0)
				return (set_env_vari(str, temp, path));
			temp = temp->next;
		}
		return (set_env_empty(str, path));
	}
	return (str);
}
