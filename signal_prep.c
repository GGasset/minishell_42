/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:11:18 by ggasset-          #+#    #+#             */
/*   Updated: 2025/05/12 13:35:16 by apaz-pri         ###   ########.fr       */
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
}

void	child_signal_behaviour(void)
{
	signal(SIGINT, SIG_DFL);
}

void	waiting_signal_behaviour(void)
{
	signal(SIGINT, waiting_signal_handler);
}


void	cntr_d(char *str, t_raw_line tokenized, t_shell *shell)
{
	if (str == NULL)
	{
		printf("exit\n");
		remove_tmp_files(shell);
        exit(0);
	}
}