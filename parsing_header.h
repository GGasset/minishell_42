
#ifndef PARSING_HEADER_H
# define PARSING_HEADER_H

# include "common_header.h"

/*
* - If quote is null or c is not a quote returns
* - If *quote is 0 and c is a quote, sets *quote to c
* - Else sets *quote to c 
*/
void	handle_quotes(char c, char *quote);

#endif