/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:57:44 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/04 11:20:26 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

void	free2(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

/*
	cmd->file = el nombre del comando/binario
	cmd->argv = parametros del comando
	cmd->input_redirect = infile
	cmd->output_redirect = outfile
*/
t_exe	prepare(t_raw_line r, t_shell *shell)
{
	t_exe	c;
	int		i;

	i = 0;
	c.command_count = 0;
	c.shell = shell;
	c.commands = malloc(sizeof(t_cmd) * r.len);
	if (!c.commands)
	{
		perror("Memory alloc Error");
		exit(EXIT_FAILURE);
	}
	while (i < r.len)
	{
		c.commands[i].path = get_from_path(r.rwcmds[i].file, shell->envp);
		c.commands[i].argv = r.rwcmds[i].argv;
		c.commands[i].input_fd = STDIN_FILENO;
		c.commands[i].output_fd = STDOUT_FILENO;
		if (r.rwcmds[i].input_redirect)
			c.commands[i].input_fd = open(r.rwcmds[i].input_redirect->file,
					O_RDONLY);
		if (r.rwcmds[i].output_redirect)
			c.commands[i].output_fd = open(r.rwcmds[i].output_redirect->file,
					O_RDWR | O_TRUNC, 0644);
		c.command_count++;
		i++;
	}
	return (c);
}

static int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (0);
}

static void	execute_builtin(t_exe exe, int j)
{
	if (ft_strcmp(exe.commands[j].argv[0], "cd") == 0)
		b_cd(exe, j);
	else if (ft_strcmp(exe.commands[j].argv[0], "echo") == 0)
		b_echo(exe.commands[j]);
	else if (ft_strcmp(exe.commands[j].argv[0], "pwd") == 0)
		b_pwd();
	else if (ft_strcmp(exe.commands[j].argv[0], "export") == 0)
		b_export(exe, j);
	else if (ft_strcmp(exe.commands[j].argv[0], "unset") == 0)
		b_unset(exe, j);
	/*else if (ft_strcmp(exe.commands[j].argv[0], "env") == 0)
		b_env(exe.shell);
	else if (ft_strcmp(exe.commands[j].argv[0], "exit") == 0)
		b_exit(exe, j);*/
}

static void	execute_binary(void)
{
	return ;
}

static void	exec_child(t_cmd *cmd, t_exe exe, int **pipes, int idx)
{
	int i;

	if (cmd->input_fd != STDIN_FILENO)
		dup2(cmd->input_fd, STDIN_FILENO);
	else if (idx > 0)
		dup2(pipes[idx - 1][0], STDIN_FILENO);
	if (cmd->output_fd != STDOUT_FILENO)
		dup2(cmd->output_fd, STDOUT_FILENO);
	else if (idx < exe.command_count-1)
		dup2(pipes[idx][1], STDOUT_FILENO);
	i = -1;
	while (++i < exe.command_count - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    if (is_builtin(cmd->argv[0]) == 0)
    {
        execute_builtin(exe, idx);
        exit(g_last_return_code);
    }
	else
	{
		if (execve(cmd->path, cmd->argv, exe.shell->envp) == -1)
		{	
			perror("execve");
			exit(errno);
		}
	}
}

void	execute(t_exe exe)
{
	int		i;
	int		**pipes;
	pid_t 	pid;
	int		status;

	pipes = malloc(sizeof(int *) * (exe.command_count -1));
	i = -1;
	while (++i < exe.command_count-1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) < 0)
			perror("Pipe: ");
	}
	i = -1;
	while (++i < exe.command_count)
	{
		pid = fork();
		if (pid < 0)
			perror("Fork:");
		else if (pid == 0)
			exec_child(&exe.commands[i], exe, pipes, i);
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < exe.command_count - 1)
			close(pipes[i][1]);
	}
	while (wait(&status) > 0)
        g_last_return_code = WEXITSTATUS(status);
    i = -1;
	while (++i < exe.command_count - 1)
        free(pipes[i]);
    free(pipes);
}

void	command(t_exe exe, t_raw_line raw, t_shell *shell)
{
	exe = prepare(raw, shell);
	execute(exe);
}