/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:47:55 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/02 13:07:12 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

t_raw_line	tokenize_line(char *line, int *err)
{
	char		**commands;
	t_raw_line	out;
	size_t		i;

	commands = ft_split(line, '|');
	out.len = ft_get_split_count(commands);
	out.raw_commands = malloc(sizeof(t_raw_cmd) * out.len);
	i = 0;
	while (err && !*err && commands && out.raw_commands && commands[i])
	{
		out.raw_commands[i] = tokenize_command(commands[i], err);
		i++;
	}
	ft_free_splitted(commands);
	if ((err && *err) || (!commands))
		free_raw_line(out);
	return (out);
}
