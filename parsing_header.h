/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:09:19 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/24 13:09:30 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_HEADER_H
# define PARSING_HEADER_H

# include "common_header.h"

/*
* - If quote is null or c is not a quote returns
* - If *quote is 0 and c is a quote, sets *quote to c
* - Else sets *quote to c 
*/
void	handle_quotes(char c, char *quote);

/*
 * Returns malloc'ed char *
 * Does not free s
*/
char	*ft_shell_replace(char *s, t_shell *shell);

#endif