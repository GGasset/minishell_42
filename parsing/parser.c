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

char	*remove_outer_quotes(char *s, int free_s)
{
	char	*out;
	char	tmp[2];
	char	quote;
	size_t	i;

	out = ft_calloc(1, 1);
	ft_bzero(&tmp, 2);
	quote = 0;
	i = 0;
	while (s && out && s[i])
	{
		tmp[0] = s[i];
		if ((!(!quote && ft_isquotes(s[i]))) && quote != s[i])
			out = ft_strjoin_free(out, tmp, TRUE, FALSE);
		handle_quotes(s[i], &quote);
		i++;
	}
	if (free_s)
		free(s);
	return (out);
}

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
