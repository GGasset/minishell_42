/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-08 14:11:18 by ggasset-          #+#    #+#             */
/*   Updated: 2025-05-08 14:11:18 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

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
}

void	child_signal_behaviour(void)
{
	signal(SIGINT, SIG_DFL);
}

void	waiting_signal_behaviour(void)
{
	signal(SIGINT, waiting_signal_handler);
}
