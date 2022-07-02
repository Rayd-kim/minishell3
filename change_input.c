/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:49:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 19:08:49 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_space(char *s)
{
	int	double_q;
	int	single_q;
	int	i;

	double_q = 0;
	single_q = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
			double_q++;
		else if (s[i] == '\'')
			single_q++;
		else if (s[i] == ' ' && double_q % 2 == 0 && single_q % 2 == 0)
			s[i] = (char)255;
		i++;
	}
}

void	change_pipe(char *s)
{
	int	double_q;
	int	single_q;
	int	i;

	double_q = 0;
	single_q = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
			double_q++;
		else if (s[i] == '\'')
			single_q++;
		else if (s[i] == '|' && double_q % 2 == 0 && single_q % 2 == 0)
			s[i] = (char)254;
		i++;
	}
}
