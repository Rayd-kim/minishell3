/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:04:15 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 14:04:16 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_home(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp("HOME=", temp->str, 5) == 0)
			return (ft_strchr(temp->str, '='));
		temp = temp->next;
	}
	return (NULL);
}

void	set_pwd(t_list *env, char *oldpwd, char *pwd)
{
	t_list	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp("OLDPWD=", temp->str, 7) == 0)
		{
			free(temp->str);
			temp->str = ft_strjoin("OLDPWD=", oldpwd);
		}
		if (ft_strncmp("PWD=", temp->str, 4) == 0)
		{
			free(temp->str);
			temp->str = ft_strjoin("PWD=", pwd);
		}
		temp = temp->next;
	}
	free(oldpwd);
	free(pwd);
}

void	write_cd_error(int error_num, char *path)
{
	write_error ("Minishell: cd: ");
	write_error (path);
	write (2, ": ", 2);
	write (2, strerror(error_num), ft_strlen(strerror(error_num)));
	write (2, "\n", 1);
	g_vari.status = error_num - 1;
}

void	bt_cd(char **arg, t_list *env, t_root *top)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (arg[1] == NULL || ft_strncmp(arg[1], "~", 2) == 0)
	{
		home = check_home(env);
		if (home == NULL)
		{
			write_error("Minishell: cd: HOME not set\n");
			g_vari.status = 1;
		}
		else if (top->in_fd == 0 && top->right == NULL)
			if (chdir(home + 1))
				write_cd_error(errno, home + 1);
	}
	else if (top->in_fd == 0 && top->right == NULL)
		if (arg[1][0] != '\0')
			if (chdir(arg[1]))
				write_cd_error(errno, arg[1]);
	pwd = getcwd(NULL, 0);
	set_pwd(env, oldpwd, pwd);
}

void	cd_process(t_root *top)
{
	int		fd[2];

	pipe(fd);
	bt_cd(top->left->right->arg, top->env, top);
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	else
		close (fd[0]);
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}
