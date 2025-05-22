/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:02:04 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/22 12:16:58 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

static void	e_child(t_cmd *cmd, t_exe exe, int **pipes, size_t idx)
{
	if (cmd->err)
		exit(1);
	if (cmd->input_fd < 0 || cmd->output_fd < 0)
	{
		perror("File descriptor");
		exit(1);
	}
	p_run(cmd, exe, pipes, idx);
	if (is_builtin(cmd->argv[0]) == 0)
	{
		b_run(exe, idx);
		exit(g_last_return_code);
	}
	else
	{
		if (execve(cmd->path, cmd->argv, exe.shell->envp))
		{
			if (!cmd->path)
				exit(127);
			else
				c_error(exe);
			exit(errno);
		}
	}
}

static void	e_wait(t_exe exe)
{
	int		status;
	size_t	i;

	i = 0;
	while (i < exe.command_count)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_last_return_code = WEXITSTATUS(status);
		i++;
	}
}

static void	e_exec(t_exe exe, int **pipes)
{
	size_t	i;
	pid_t	pid;

	i = -1;
	while (++i < exe.command_count)
	{
		pid = fork();
		if (pid < 0)
			perror("Fork:");
		else if (pid == 0)
		{
			exe.commands[i].pid = pid;
			e_child(&exe.commands[i], exe, pipes, i);
		}
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < exe.command_count - 1)
			close(pipes[i][1]);
	}
}

static void	p_free(int **pipes, size_t command_count)
{
	size_t	i;

	i = 0;
	while (i < command_count - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	e_run(t_exe exe)
{
	int	**pipes;

	pipes = malloc(sizeof(int *) * (exe.command_count - 1));
	p_create(pipes, exe);
	child_signal_behaviour();
	e_exec(exe, pipes);
	signal(SIGINT, waiting_signal_handler);
	signal(SIGQUIT, core_dump);
	signal(SIGCHLD, SIG_DFL);
	e_wait(exe);
	p_free(pipes, exe.command_count);
}
