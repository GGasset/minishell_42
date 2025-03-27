/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:09:19 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/27 14:52:34 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HEADER_H
# define PARSING_HEADER_H

# include "common_header.h"

// Common Utils

/*
* - If quote is null or c is not a quote returns
* - If *quote is 0 and c is a quote, sets *quote to c
* - Else if *quote is c *quote is set to 0
*/
void			handle_quotes(char c, char *quote);
char			get_quote_at_point(char *s, size_t point);

int				is_operator(char c);
int				is_word_delimiter(char c);

/*
* # Behaviour
* Skips starting white_spaces (should be normalized by this point)
* If delimiter is different of 0, is set as the char that was the delimiter
* Checks for quotes and doesn't count spaces in them as word delimiters
*	-	- Operator characters count as word delimiters outside quotes
*	-	-	i.e. echo|cat>out     echo"|"cat">"out
*	-	- Because of quotes its recommended for s to be the start of the string
*	-	-	- To evade possible errors
* ## Return Value
* Returns the next word
* Returns NULL in case of error or if a word delimiter is found at start
*	- Word delimiters other than spaces
* ## Memory management
* Returns malloc'ed pointer
*/
char			*shell_get_word(char *s, size_t start, char *delimiter);

/*
* # Behaviour
* Similar to shell_get_word
* ## Return Value
* Returns the index of the start of the next word
* On string end, returns the pointer to the NULL character
*	- String end should be checked with char *delimiter of shell_get_word
*/
size_t			get_next_word_start_i(char *s, size_t start);

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
char			*ft_shell_replace(char *s, t_shell *shell);

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
char			*ft_normalize_spaces(char *s, int free_s);
int				*check_invalid_quotes(char *s);

// Tokenization with finite state machines

enum e_states
{
	state_err = 0,
	input_parsing,
	command_parsing,
	output_parsing
};

/*
* # Behaviour
* Sets start to the start of the next token
* Sets err to true in case of state misalignment
*	- i.e. "<in > out"
*	-	- This is incorrect although could be thougth of of copying in to out
*
* Sets state to new state if needed
* ### Memory handling
* Returns malloc'ed struct
*
* ### Important cases
* echo "a | cat"
*/
t_raw_cmd		*parse_token(char **start, int *err, enum e_states *state);

// Start is set on the start of the next operator
t_raw_cmd		*parse_stdin(char **start);
// Start is set on the start of the next operator
t_raw_cmd		*parse_stdout(char **start);
// Checks if there is a pipe next
// Start is set on the start of the next operator or the command
t_raw_cmd		*parse_command(char **start);

// Finite state machine utils

enum e_states	get_state(enum e_operators op);
int				is_compatible(enum e_states prev, enum e_states next);

#endif