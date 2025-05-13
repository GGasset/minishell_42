/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:07:23 by ggasset-          #+#    #+#             */
/*   Updated: 2025/05/12 19:12:08 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"
#include "execution_header.h"

void	free_raw_line(t_raw_line *line, int free_line)
{
	size_t		i;
	t_raw_cmd	command;

	if (!line)
		return ;
	i = 0;
	while (line->rwcmds && i < line->len)
	{
		command = line->rwcmds[i];
		free(command.file);
		ft_free_splitted(command.argv);
		if (command.input_redirect)
			free(command.input_redirect->file);
		free(command.input_redirect);
		if (command.output_redirect)
			free(command.output_redirect->file);
		free(command.output_redirect);
		ft_bzero(line->rwcmds + i, sizeof(t_raw_cmd));
		i++;
	}
	free(line->rwcmds);
	line->rwcmds = 0;
	if (free_line)
		free(line);
}

void	remove_tmp_files(t_shell *shell)
{
	char	**files;
	size_t	i;

	if (!shell || !shell->tmp_files)
		return ;
	files = ft_split(shell->tmp_files, '|');
	i = 0;
	while (files && files[i])
	{
		unlink(files[i]);
		i++;
	}
	ft_free_splitted(files);
	free(shell->tmp_files);
	shell->tmp_files = 0;
}

void	free_execution_env(t_exe exe)
{
	size_t	i;

	i = 0;
	while (exe.commands && i < exe.command_count)
	{
		ft_free_splitted(exe.commands[i].argv);
		free(exe.commands[i].path);
		i++;
	}
	free(exe.commands);
}

void	exit_call(t_shell *s, t_raw_line *lines, t_exe *structure, int code)
{
	free_raw_line(lines, FALSE);
	free_execution_env(*structure);
	remove_tmp_files(s);
	if (s)
		ft_free_splitted(s->envp);
	rl_clear_history();
	exit(code);
}
