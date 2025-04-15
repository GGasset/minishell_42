/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:57:44 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/04/15 19:29:56 by apaz-pri         ###   ########.fr       */
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
t_exe	prepare(t_raw_line rwcmd, t_shell *shell)
{
	t_exe   cmd;
	int		i;

	i = 0;
	cmd.command_count = 0;
	while (rwcmd.raw_commands->file != NULL)
	{
		cmd.commands[i].path = get_from_path(rwcmd.raw_commands->file,
		shell->envp);
		cmd.commands[i].argv = rwcmd.raw_commands->argv;
		if (rwcmd.raw_commands->input_redirect)
			cmd.commands[i].input_fd = open(rwcmd.raw_commands->input_redirect->file, 
			O_RDONLY);
		if (rwcmd.raw_commands->output_redirect)
			cmd.commands[i].output_fd = open(rwcmd.raw_commands->output_redirect->file, 
			O_CREAT | O_RDWR | O_TRUNC);
		cmd.command_count++;
	}
	return (cmd);
}
