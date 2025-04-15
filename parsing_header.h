/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:09:19 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/03 17:08:16 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HEADER_H
# define PARSING_HEADER_H

# include "common_header.h"

# define heredoc_prompt "\n> "

// Common Utils

/*
* - If quote is null or c is not a quote returns
* - If *quote is 0 and c is a quote, sets *quote to c
* - Else if *quote is c, *quote is set to 0
*/
void			handle_quotes(char c, char *quote);
char			get_quote_at_point(char *s, size_t point);

int				is_operator(char c);
int				is_word_delimiter(char c);

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

// Returns true for invalid quoting
int				check_invalid_quotes(char *s);

// Tokenization prepocessing

/*
# Behaviour
* Skips starting white_spaces (should be normalized by this point)
* If delimiter is different of 0, is set as the char that was the delimiter
*	- Follows e_operator structure logic
*	- In case of delimiter being a space.
*	-	- Checks next char and if is a delimiter sets delimiter pointer to it.
*	-	- Spects normalized spaces at this point.
*	-	- So it may reliably be used to check next operator.
* Checks for quotes and doesn't count anything in them as word delimiters
*	-	- Operator characters count as word delimiters outside quotes
*	-	-	i.e. ``` echo|cat>out     echo"|"cat">"out```
*	-	- Because of quotes its recommended for s to be the start of the string
*	-	-	- To evade possible errors
## Return Value
* Returns the next word
* Returns NULL in case of error or if a word delimiter is found at start
*	- Word delimiters other than spaces
 # Memory management
* Returns malloc'ed pointer
*/
char			*shell_get_word(char *s, size_t start, char *delimiter);

/*
* # Behaviour
* Similar to shell_get_word at word recognition
* 1. Skips word delimiters
* 2. Skips word
* 3. Skips word delimiter
* ## Return Value
* Returns the index of the start of the next word
* On string end, returns the pointer to the NULL character
*	- String end should be checked with char *delimiter of shell_get_word
* ## Use
* Used to move index for next shell_get_word call
*/
size_t			get_next_word_start_i(char *s, size_t start);

// Returns the index of the first char that is not part of the word
// If start is the index of a delimiter skips delimiters until it finds a word
// Checks for quotes
size_t			skip_word(char *s, size_t start);

// Tokenization

// # Behaviour
// Handles null argv parameter
// Free's old argv
// Dup's s
char			**argv_append(char **argv, char *s, int free_s);

// Split but skips delimiter characters inside quotes
char			**shell_split(char *s, char c);
t_raw_line		tokenize_line(char *line, int *err, t_shell *shell);

void			remove_quotes(t_raw_line tokens);// NEEDS TESTING

// If something is wrong do nothing
char			*do_heredoc(char *delimiter, size_t i); // Needs Testing

#endif