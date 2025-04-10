/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 12:07:23 by ggasset-          #+#    #+#             */
/*   Updated: 2025-04-07 12:07:23 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

void	free_raw_line(t_raw_line *line, int free_line)
{
	size_t      i;
	t_raw_cmd   command;

	if (!line)
		return ;
	i = 0;
	while (line->raw_commands && i < line->len)
	{
		command = line->raw_commands[i];
		free(command.file);
		ft_free_splitted(command.argv);
		if (command.input_redirect)
			free(command.input_redirect->file);
		free(command.input_redirect);
		if (command.output_redirect)
			free(command.output_redirect->file);
		free(command.output_redirect);
		ft_bzero(line->raw_commands + i, sizeof(t_raw_cmd));
		i++;
	}
	free(line->raw_commands);
	line->raw_commands = 0;
	if (free_line)
		free(line);
}
