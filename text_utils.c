/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:59:31 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/20 17:05:32 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

void	handle_quotes(char c, char *quote)
{
	if (!quote || !ft_isquotes(c))
		return ;
	if (*quote == c)
		*quote = 0;
	else if (*quote == 0)
		*quote = c;
}
