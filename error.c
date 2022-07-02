/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:33 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 21:21:48 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_stdin(char *str, int check)
{
	if (check == 1)
	{
		write (2, "Minishell: ", 11);
		write (2, str, ft_strlen(str));
		write (2, ": ", 2);
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
		g_vari.status = 127;
		exit (127);
	}
	else
	{
		write (2, "Minishell: ", 11);
		write (2, str, ft_strlen(str));
		write (2, ": ", 2);
		write (2, "command not found\n", 18);
		g_vari.status = 127;
		exit (127);
	}
}

void	write_error(char *str)
{
	write (2, str, ft_strlen(str));
}
