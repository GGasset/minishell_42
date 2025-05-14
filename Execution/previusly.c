/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   previusly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:59:24 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/14 12:00:44 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

t_exe	prepare(t_raw_line r, t_shell *shell)
{
	t_exe	c;
	size_t	i;

	i = 0;
	c.command_count = 0;
	c.shell = shell;
	c.commands = malloc(sizeof(t_cmd) * r.len);
	if (!c.commands)
		exit(EXIT_FAILURE);
	while (i < r.len)
	{
		c.commands[i].path = get_from_path(r.rwcmds[i].file, shell->envp);
		c.commands[i].argv = ft_splitdup(r.rwcmds[i].argv);
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
