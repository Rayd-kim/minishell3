/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:02:42 by youskim           #+#    #+#             */
/*   Updated: 2022/07/02 14:02:43 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection(char *file_name, int check)
{
	int	fd;
	int	file_check;

	if (check == 1)
	{
		file_check = open (file_name, O_RDONLY);
		if (file_check != -1)
		{
			close (file_check);
			unlink (file_name);
		}
		fd = open (file_name, O_WRONLY | O_CREAT, 0644);
		return (fd);
	}
	else
	{
		file_check = open (file_name, O_WRONLY | O_APPEND);
		if (file_check != -1)
			fd = file_check;
		else
			fd = open (file_name, O_WRONLY | O_CREAT, 0644);
		return (fd);
	}
}

int	open_file(char *file)
{
	int	fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
	{
		write (2, "Minishell: ", 11);
		write (2, file, ft_strlen(file));
		write (2, ": ", 2);
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
		g_vari.status = errno - 1;
	}
	return (fd);
}
