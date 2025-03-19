/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:08:42 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/19 18:00:03 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

// Gets next dollarsign outside single quotes (')
static char	*get_next_dollar(char *s)
{
	size_t	i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (s[i])
	{
		handle_quotes(s[i], &quotes);
		if (quotes != '\'' && s[i] == '$' && ft_isalnum(s[i + 1]))
			return (s + i);
		i++;
	}
	return (0);
}

char	*ft_shell_replace(char *s, char **envp)
{
	
}
