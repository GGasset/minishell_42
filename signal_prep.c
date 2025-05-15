/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:11:18 by ggasset-          #+#    #+#             */
/*   Updated: 2025/05/14 12:46:26 by apaz-pri         ###   ########.fr       */
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

void	heredoc_signal_handler(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		printf("\n");
		fd = open(".heredoco", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		close(fd);
		close(0);
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
	signal(SIGQUIT, SIG_DFL);
	signal(SIGCHLD, SIG_IGN);
}
