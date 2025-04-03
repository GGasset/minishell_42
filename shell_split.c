/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:06:51 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/03 17:07:26 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

static char	**handle_error(char **arr, char *to_add)
{
	ft_free_splitted(arr);
	free(to_add);
	return ((char **)0);
}

static ssize_t	shell_strchr(char *s, ssize_t start, char c)
{
	char	quotes;
	ssize_t	i;

	if (start == -1)
		return (-1);
	quotes = get_quote_at_point(s, start);
	i = (ssize_t)start;
	while (s[i])
	{
		if (s[i] == c && !quotes)
			return (i);
		handle_quotes(s[i], &quotes);
		i++;
	}
	return (-1);
}

char	**shell_split(char *s, char c)
{
	char	**out;
	char	*tmp;
	char	quote;
	ssize_t	i[2];
	ssize_t	split_len;

	out = ft_calloc(1, sizeof(char *));
	ft_bzero(i, sizeof(size_t) * 2);
	split_len = shell_strchr(s, 0, c);
	while (out && split_len != -1)
	{
		out = ft_realloc(out, sizeof(char *) * i[0] + 1,
			sizeof(char *) * i[0] + 2,  TRUE);
		tmp = ft_substr(s, i[1], split_len);
		if (!tmp || !out)
			return (handle_error(out, tmp));
		out[i[0]] = tmp;
		i[1] += split_len;
		split_len = shell_strchr(s, i[1], c) - i[1];
		i[0]++;
	}
	return (out);
}
