/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:08:42 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/27 15:49:10 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

static int	is_valid_env_char(char c)
{
	return (ft_isalnum(c) || c == '?');
}

// Gets next dollarsign outside single quotes (')
// If dollarsign is followed by a non alpha numeric character is ignored
static size_t	get_next_dollar(char *s, size_t start)
{
	size_t	i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (i < start)
	{
		handle_quotes(s[i], &quotes);
		i++;
	}
	while (s && s[i])
	{
		handle_quotes(s[i], &quotes);
		if (s[i] == '$' && quotes != '\'' && is_valid_env_char(s[i + 1])
			&& ((s[i + 1] == '?' && ft_isspace(s[i + 2])) || s[i + 1] != '?'))
			return (i - start + 1);
		i++;
	}
	return (0);
}

// Gets the length of the valid sequence for replace
static size_t	get_replaced_len(char *s)
{
	size_t	i;

	i = 0;
	if (s && s[i] == '?')
		return (1);
	while (s && ft_isalnum(s[i]))
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
	if (*s == '?')
		return (ft_itoa(g_last_return_code));
	tmp = ft_substr(s, 0, len);
	out = ft_strdup(get_envp(tmp, shell->envp));
	if (!out)
		out = ft_strdup("");
	free(tmp);
	return (out);
}

char	*ft_shell_replace(char *s, t_shell *shell)
{
	char	*out;
	size_t	replace_start;
	char	*replacer;
	size_t	dollar_i;
	size_t	tmp;

	if (!s || !shell)
		return (0);
	out = ft_strdup(s);
	dollar_i = get_next_dollar(s, 0);
	replace_start = dollar_i;
	while (dollar_i)
	{
		replacer = get_replacer_text(s + dollar_i, shell);
		out = ft_index_replace(out, replace_start - 1,
				get_replaced_len(s + dollar_i) + 1, replacer);
		dollar_i += get_replaced_len(s + dollar_i);
		tmp = get_next_dollar(s, dollar_i);
		replace_start += ft_strlen(replacer) - 1 + tmp;
		free(replacer);
		if (!get_next_dollar(s, dollar_i))
			return (out);
		dollar_i += tmp;
	}
	return (out);
}
