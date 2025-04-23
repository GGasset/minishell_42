/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_splitted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-22 17:35:08 by ggasset-          #+#    #+#             */
/*   Updated: 2025-04-22 17:35:08 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitdup(char **splitted)
{
	char	**out;
	size_t	out_len;
	size_t	i;

	if (!splitted)
		return (0);
	out_len = ft_get_split_count(splitted);
	out = ft_calloc(out_len, sizeof(char *));
	i = 0;
	while (out && i < out_len)
	{
		out[i] = ft_strdup(splitted[i]);
		i++;
	}
	return (out);
}
