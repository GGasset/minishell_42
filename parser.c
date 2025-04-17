/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-17 13:25:59 by ggasset-          #+#    #+#             */
/*   Updated: 2025-04-17 13:25:59 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

t_raw_line	parse_input(char *line, int *err, t_shell *shell)
{
	t_raw_line	out;

	ft_bzero(&out, sizeof(t_raw_line));
	if (check_invalid_quotes(line))
	{
		*err = TRUE;
		return (out);
	}
	line = ft_shell_replace(line, shell);
	line = ft_normalize_spaces(line, TRUE);
	if (!line)
	{
		*err = TRUE;
		return (out);
	}
	out = tokenize_line(line, err, shell);
	free(line);
	return (out);
}
