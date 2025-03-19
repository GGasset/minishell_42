/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:59:31 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/19 18:00:20 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

void	handle_quotes(char c, char *quote)
{
	if (!quote || !ft_isquotes(*quote))
		return ;
	if (*quote == c)
		*quote = 0;
	else
		*quote = c;
}

int	is_envvar_char(char c)
{
	return 0;
}
