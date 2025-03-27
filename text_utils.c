/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:59:31 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/27 12:48:25 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

void	handle_quotes(char c, char *quote)
{
	if (!quote || !ft_isquotes(c))
		return ;
	if (*quote == c)
		*quote = 0;
	else if (*quote == 0)
		*quote = c;
}

int	check_invalid_quotes(char *s)
{
	char	out;
	size_t	i;

	out = 0;
	i = 0;
	while (s && s[i])
	{
		handle_quotes(s[i], &out);
		i++;
	}
	return (out != 0);
}

int	is_word_delimiter(char c)
{
	if (ft_isspace(c))
		return (TRUE);
	if (c == '<' || c == '>' || c == '|')
		return (TRUE);
	return (FALSE);
}

char	get_quote_at_point(char *s, size_t point)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (s && s[i] && i < point)
	{
		handle_quotes(s[i], &quote);
		i++;
	}
	return (quote);
}
