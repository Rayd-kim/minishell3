/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:11:00 by youskim           #+#    #+#             */
/*   Updated: 2022/07/01 15:11:01 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	kill_process(int *process)
{
	pid_t	pid;
	int		check;

	*process = 0;
	while (1)
	{
		pid = waitpid(0, &check, 0);
		if (pid != -1)
		{
			*process += 1;
			kill (pid, SIGKILL);
		}
		else
			break ;
	}
}

// void setup_term(void)
// {
//     struct termios t;

//     tcgetattr(0, &t);
//     t.c_lflag &= ~ECHOCTL;
//     tcsetattr(0, TCSANOW, &t);
// }

void	new_line(void)
{
	g_vari.status = 1;
	rl_on_new_line();
	rl_redisplay();
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(int sig)
{
	int		process;

	kill_process(&process);
	// setup_term();
	if (sig == CTRL_C && g_vari.flag == 1 && process == 0)
	{
		g_vari.status = 130;
		g_vari.flag = dup(0);
		write (1, ">  \n", 4);
		close(0);
	}
	else if (sig == CTRL_C && process == 0 && g_vari.flag > 1)
	{
		g_vari.status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == CTRL_C && process == 0)
		new_line();
	else if (sig == CTRL_C && process != 0)
	{
		g_vari.status = 130;
		write (1, "\n", 1);
	}
}

void	signal_handler_2(int sig)
{
	int		process;

	kill_process(&process);
	if (process != 0 && sig == CTRL_SLASH)
		write (1, "Quit: 3\n", 8);
}

void	set_signal(int sig)
{
	if (sig == SIGUSR1)
		signal(CTRL_SLASH, SIG_IGN);
	else
		signal(CTRL_SLASH, signal_handler_2);
	signal (CTRL_C, signal_handler);
}
