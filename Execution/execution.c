/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:57:44 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/22 14:11:14 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

void b_alone(t_exe exe, int j)
{
	int cp_in;

	cp_in = dup(STDIN_FILENO);
    if (exe.commands[j].input_fd != STDIN_FILENO)
        dup2(exe.commands[j].input_fd, STDIN_FILENO);
    if (exe.commands[j].output_fd != STDOUT_FILENO)
        dup2(exe.commands[j].output_fd, STDOUT_FILENO);
    b_run(exe, j);
    dup2(cp_in, STDIN_FILENO);
    close(cp_in);
}
	
void	command(t_exe exe, t_raw_line raw, t_shell *shell)
{
	exe = prepare(raw, shell);
	free_raw_line(&raw, FALSE);
	if (exe.command_count == 1 && !is_builtin(exe.commands[0].argv[0])
		&& !exe.commands[0].err)
		{
			b_alone(exe, 0);
		}
	else if (!(exe.command_count == 1 && !exe.commands[0].argv[0]))
		e_run(exe);
	free_execution_env(exe);
}