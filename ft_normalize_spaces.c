/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:49:09 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/24 18:41:10 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

static char	*trim_space(char *s, int free_s)
{
	char	*out;

	if (!s)
		return (0);
	out = ft_strtrim(s, " ");
	if (free_s)
		free(s);
	return (out);
}

static char	normalize_spaces(char c)
{
	if (ft_isspace(c))
		c = ' ';
	return (c);
}

static char	*append_normalized(char *s, char *out, size_t i, char quote)
{
	char	tmp[2];

	tmp[0] = normalize_spaces(s[i]);
	tmp[1] = 0;
	if (!ft_isspace(s[i])
		|| (i && ft_isspace(s[i]) && !ft_isspace(s[i - 1]))
		|| quote)
		out = ft_strjoin_free(out, tmp, TRUE, FALSE);
	return (out);
}

char	*ft_normalize_spaces(char *s, int free_s)
{
	char	*out;
	size_t	i;
	char	quote;

	if (!s)
		return (0);
	out = ft_strdup("");
	if (!out)
		return (0);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	quote = 0;
	while (out && s[i])
	{
		handle_quotes(s[i], &quote);
		out = append_normalized(s, out, i, quote);
		i++;
	}
	if (free_s)
		free(s);
	out = trim_space(out, TRUE);
	return (out);
}
