/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:36:38 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/27 16:28:10 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

static char	set_delimiter(char *s, size_t start, size_t len)
{
	if (ft_isspace(s[start + len]) && is_word_delimiter(s[start + len + 1]))
		return (s[start + len + 1]);
	else
		return (s[start + len]);
	return (0);
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
	while (quote || !is_word_delimiter(s[start]))
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
