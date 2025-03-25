/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:09:19 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/25 12:30:03 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_HEADER_H
# define PARSING_HEADER_H

# include "common_header.h"

// Common Utils

/*
* - If quote is null or c is not a quote returns
* - If *quote is 0 and c is a quote, sets *quote to c
* - Else sets *quote to c 
*/
void	handle_quotes(char c, char *quote);


// Environment variables

/*
# Behaviour
* * Checkea cuales comillas son las que le rodean de mas afuera
(no reemplazar en caso de comillas simples) 
y sustituya las variables
* * HM="          a       asd    |"
* * echo $HM
* * echo "$HM"
* * Solo son validos para expandir los caracteres alfanumericos
* * Al expandir solo buscara hasta que no halla caracteres valido
* * $[caracter no valido] o $ no sera considerado como valido para expandir 
y  sera ignorado, se buscara el proximo $
* * Caso especial
* * echo $?a

### Memory handling
 * Returns malloc'ed char *
 * Does not free s
*/
char	*ft_shell_replace(char *s, t_shell *shell);


// Normalization and simple errors

/*
* # Behaviour
* Normalize any white-space char into a single space
* Trims starting and ending whitspace chars
* Does not do nothing inside single or double quotes
* See:
*	- man isspace

* ### Memory handling
* Returns malloc'ed pointer
*/
char	*ft_normalize_spaces(char *s, int free_s);
int		*check_invalid_quotes(char *s);


// Tokenization with finite state machines

enum e_states
{
	input_parsing,
	command_parsing,
	output_parsing
};

#endif