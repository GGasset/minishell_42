/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:02:28 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/26 12:32:09 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*output;

	len = ft_strlen(s);
	output = malloc(len + 1);
	i = 0;
	while (i < len && output)
	{
		output[i] = s[i];
		i++;
	}
	if (output)
		output[len] = 0;
	return (output);
}
