/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:11:26 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/14 12:55:29 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

static void	close_pipes(int **pipes, size_t command_count)
{
	size_t	i;

	i = 0;
	while (i < command_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	dup_pipes(t_cmd *cmd, t_exe exe, int **pipes, size_t idx)
{
	if (cmd->input_fd != STDIN_FILENO)
		dup2(cmd->input_fd, STDIN_FILENO);
	else if (idx > 0)
		dup2(pipes[idx - 1][0], STDIN_FILENO);
	if (cmd->output_fd != STDOUT_FILENO)
		dup2(cmd->output_fd, STDOUT_FILENO);
	else if (idx < exe.command_count - 1)
		dup2(pipes[idx][1], STDOUT_FILENO);
}

void	p_create(int **pipes, t_exe exe)
{
	size_t	i;

	i = -1;
	while (++i < exe.command_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) < 0)
			perror("Pipe: ");
	}
}

void	p_run(t_cmd *cmd, t_exe exe, int **pipes, size_t idx)
{
	dup_pipes(cmd, exe, pipes, idx);
	close_pipes(pipes, exe.command_count);
}
