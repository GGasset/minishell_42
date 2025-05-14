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

static char	*replace_squiggly(char *s, int free_s, t_shell *shell)
{
	char	*out;
	size_t	out_len;
	char	*replacer;
	size_t	i;

	replacer = get_user_home(shell);
	out = ft_calloc(1, sizeof(char));
	out_len = 0;
	i = 0;
	while (s && out && s[i])
	{
		if (s[i] == '~' && (!i || is_word_delimiter(s[i - 1]))
			&& (s[i + 1] == '/' || is_word_delimiter(s[i + 1])) && replacer)
			out = ft_strjoin_free(out, replacer, TRUE, FALSE);
		else
		{
			out = ft_realloc(out, out_len + 1, out_len + 2, TRUE);
			out[out_len] = s[i];
		}
		out_len = ft_strlen(out);
		i++;
	}
	free(replacer);
	free((void *)((free_s != 0) * (size_t)s));
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
	if (line)
		line = replace_squiggly(line, TRUE, shell);
	if (!line)
	{
		*err = TRUE;
		return (out);
	}
	if (line[0])
		out = tokenize_line(line, err, shell);
	else
		ft_bzero(&out, sizeof(t_raw_line));
	free(line);
	return (out);
}
