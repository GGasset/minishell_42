/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:11:18 by ggasset-          #+#    #+#             */
/*   Updated: 2025/05/12 19:37:47 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"
#include "execution_header.h"

void	prompt_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	waiting_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
	}
}

void	prompt_signal_behaviour(void)
{
	signal(SIGINT, prompt_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

void	child_signal_behaviour(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	waiting_signal_behaviour(void)
{
	signal(SIGINT, waiting_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	cntr_d(char *str, t_raw_line r, t_exe exe)
{
	if (str == NULL)
	{
		printf("exit\n");
		exit_call(exe.shell, &r, &exe, 0);
	}
}