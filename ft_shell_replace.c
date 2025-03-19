/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:08:42 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/19 19:47:13 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

static int	is_valid_env_char(char c)
{
	return (ft_isalnum(c) || c == '?');
}

// Gets next dollarsign outside single quotes (')
// If dollarsign is followed by a non alpha numeric character is ignored
static char	*get_next_dollar(char *s)
{
	size_t	i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (s && s[i])
	{
		handle_quotes(s[i], &quotes);
		if (s[i] == '$' && quotes != '\'' && ft_isalnum(s[i + 1]))
			return (s + i);
		i++;
	}
	return (0);
}

// Gets the length of the valid sequence for replace
static size_t	get_replaced_len(char *s)
{
	size_t	i;

	i = 0;
	if (s && s[0] == '$')
		s++;
	while (s && ft_isalnum(s[i]))
		i++;
	if (s && s[i] == '?')
		i++;
	return (i);
}

// * Gets the correspoding value for a value after $
// * s is the pointer to that $
// ## Returns a malloc'ed pointer
static char	*get_replacer_text(char *s, t_shell *shell)
{
	size_t	len;
	char	*tmp;
	char	*out;

	if (!s || !shell)
		return (0);
	len = get_replaced_len(s);
	if (*s == '$')
		s++;
	if (*s == '?')
		return (ft_itoa(shell->last_return_code));
	tmp = ft_substr(s, 0, len);
	if (!out)
		return (0);
	out = ft_strdup(get_envp(tmp, shell->envp));
	free(tmp);
	return (out);
}

char	*ft_shell_replace(char *s, t_shell *shell)
{
	
}
