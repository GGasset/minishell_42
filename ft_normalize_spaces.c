/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:49:09 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/24 15:33:18 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

char	*trim_space(char *s, int free_s)
{
	char	*out;

	if (!s)
		return (0);
	out = ft_strtrim(s, " ");
	if (free_s)
		free(s);
	return (out);
}

char	normalize_spaces(char c)
{
	if (ft_isspace(c))
		c = ' ';
	return (c);
}

char	*ft_normalize_spaces(char *s, int free_s)
{
	char	*out;
	size_t	i;
	char	tmp[2];

	if (!s)
		return (0);
	out = ft_strdup("");
	if (!out)
		return (0);
	tmp[1] = 0;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	while (out && s[i])
	{
		tmp[0] = normalize_spaces(s[i]);
		if (!ft_isspace(s[i])
			|| (i && ft_isspace(s[i]) && !ft_isspace(s[i - 1])))
			out = ft_strjoin_free(out, tmp, TRUE, FALSE);
		i++;
	}
	if (free_s)
		free(s);
	out = trim_space(out, TRUE);
	return (out);
}
