/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:36:38 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/03 15:15:32 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

static char	set_delimiter(char *s, size_t start, size_t len, int *err)
{
	char	out;
	size_t	i;

	*err = *err;
	i = start + len;
	if (s[i] && is_word_delimiter(s[i]) && is_word_delimiter(s[i + 1]))
	{
		if (ft_isspace(s[i]))
			i++;
		out = s[i];
		if (!s[i])
			return (0);
		i++;
		if (s[i] == out && is_redirect_operator(s[i]))
			out++;
		if (is_redirect_operator(s[i + 1]))
			*err = 1;
		return (out);
	}
	else
		return (s[start + len]);
	return (0);
}

size_t	skip_word(char *s, size_t start)
{
	char	quotes;

	quotes = get_quote_at_point(s, start);
	while (is_word_delimiter(s[start]) && s[start] && !quotes)
		start++;
	while ((!is_word_delimiter(s[start]) || quotes) && s[start])
	{
		handle_quotes(s[start], &quotes);
		start++;
	}
	return (start);
}

size_t	get_next_word_start_i(char *s, size_t start)
{
	char	quote;

	if (!s)
		return (0);
	quote = get_quote_at_point(s, start);
	while ((quote || !is_word_delimiter(s[start])) && s[start])
	{
		handle_quotes(s[start], &quote);
		start++;
	}
	while (!quote && is_word_delimiter(s[start]) && s[start])
	{
		handle_quotes(s[start], &quote);
		start++;
	}
	return (start);
}

char	*shell_get_word(char *s, size_t i, char *delimiter, int *er)
{
	char	quote;
	size_t	len;

	if (!s)
		return (0);
	while (ft_isspace(s[i]))
		i++;
	quote = get_quote_at_point(s, i);
	len = 0;
	while (quote || !is_word_delimiter(s[i + len]))
	{
		if (!s[i + len])
			break ;
		handle_quotes(s[i + len], &quote);
		len++;
	}
	if (delimiter)
		*delimiter = set_delimiter(s, i, len, er);
	if (!len)
		return (0);
	return (ft_substr(s, i, len));
}
