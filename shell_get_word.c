/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:36:38 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/27 13:16:12 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

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
		*delimiter = s[start + len];
	if (!len)
		return (0);
	return (ft_substr(s, start, len));
}
