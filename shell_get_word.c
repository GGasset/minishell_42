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

static char	set_delimiter(char *s, size_t start, size_t len)
{
	char	out;
	size_t	i;

	i = start + len + 1;
	if (ft_isspace(s[start + len]) && is_word_delimiter(s[i]))
	{
		out = s[i];
		if (!s[i] || !is_operator(s[i]))
			return (0);
		if (ft_isspace(s[i + 1]))
			i++;
		i++;
		if (s[i] == out && is_redirect_operator(s[i]))
			out++;
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
	while (!quote && is_word_delimiter(s[start]) && s[start])
	{
		handle_quotes(s[start], &quote);
		start++;
	}
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

char	*shell_get_word(char *s, size_t start, char *delimiter)
{
	char	quote;
	size_t	len;

	if (!s)
		return (0);
	while (ft_isspace(s[start]))
		start++;
	quote = get_quote_at_point(s, start);
	len = 0;
	while (quote || !is_word_delimiter(s[start + len]))
	{
		if (!s[start + len])
			break ;
		handle_quotes(s[start + len], &quote);
		len++;
	}
	if (delimiter)
		*delimiter = set_delimiter(s, start, len);
	if (!len)
		return (0);
	return (ft_substr(s, start, len));
}
