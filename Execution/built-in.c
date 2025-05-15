/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:01:02 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/15 18:30:18 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (0);
	return (1);
}

void	b_run(t_exe exe, int j)
{
	g_last_return_code = 0;
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
	else if (ft_strcmp(exe.commands[j].argv[0], "env") == 0)
		b_env(exe.shell->envp);
	else if (ft_strcmp(exe.commands[j].argv[0], "exit") == 0)
		b_exit(exe, j);
}
