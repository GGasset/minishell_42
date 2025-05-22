/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   previusly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:59:24 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/22 13:10:24 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

static void set_path(t_exe *c, t_raw_line r,  size_t i, t_shell *shell)
{
    if (ft_strchr(r.rwcmds[i].file, '/'))
    {
        if (access(r.rwcmds[i].file, F_OK) == 0)
            c->commands[i].path = ft_strdup(r.rwcmds[i].file);
        else
            c->commands[i].path = NULL;
    }
    else
        c->commands[i].path = get_from_path(r.rwcmds[i].file, shell->envp);
}

static void raw_cmd_prepare(t_exe *c, t_raw_line *r, t_shell *shell, size_t i)
{
	set_path(c, *r, i, shell);
	c->commands[i].argv = ft_splitdup(r->rwcmds[i].argv);
	c->commands[i].input_fd = STDIN_FILENO;
	c->commands[i].output_fd = STDOUT_FILENO;
	if (r->rwcmds[i].input_redirect)
		c->commands[i].input_fd = open(r->rwcmds[i].input_redirect->file,
				O_RDONLY);
	if (r->rwcmds[i].output_redirect)
		c->commands[i].output_fd = open(r->rwcmds[i].output_redirect->file,
				O_RDWR | O_TRUNC, 0644);
	c->commands[i].err = r->rwcmds[i].err;
}

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
		raw_cmd_prepare(&c, &r, shell, i);
		c.command_count++;
		i++;
	}
	return (c);
}
