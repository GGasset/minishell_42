/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:08:42 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/19 19:21:47 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

// Gets next dollarsign outside single quotes (')
// If dollarsign is inside single quotes or followed by a non alpha numeric character is ignored
static char	*get_next_dollar(char *s)
{
	size_t	i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (s[i])
	{
		handle_quotes(s[i], &quotes);
		if (s[i] == '$' && quotes != '\'' && ft_isalnum(s[i + 1]))
			return (s + i);
		i++;
	}
	return (0);
}

char	*ft_shell_replace(char *s, char **envp)
{
	
}
