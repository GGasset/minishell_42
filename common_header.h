/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:13:38 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/24 17:39:17 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_HEADER_H
# define COMMON_HEADER_H

# include <stddef.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

enum e_operators
{
	none = 0,
	stdin_redirect = '<',
	stdin_delimiter = '<' + 1,
	stdout_redirect = '>',
	stdout_append = '>' + 1,
	pipe_op = '|'
};

typedef struct s_raw_cmd
{
	char				*file;
	char				**argv;
	enum e_operators	type;
}		t_raw_cmd;

/*
 * example "<in cat | cat>outi"
 raw_commands:
	- {in, 0, stdin_redirect}
	- {cat, {"cat", 0}, pipe}
	- {cat, {"cat", 0}, pipe}
	- {outi, 0, stdout_redirect}
 len: 4
 * example "<< "EOF" cat | cat -e | cat"
 raw_commands:
	- {EOF, 0, stdin_delimiter}
	- {cat, {"cat", 0}, pipe}
	- {cat, {"cat", "-e", 0}, pipe}
	- {cat, {"cat", 0}, pipe}
 * example "<in cat"
 raw_commands:
	- {in, 0, stdin_redirect}
	- {cat, {"cat", 0}, none}
 * example "<in cat > out"
	- {in, 0, stdin_redirect}
	- {cat, {"cat", 0}, none}
	- {out, 0, stdout_redirect}
*/
typedef struct s_raw_line
{
	t_raw_cmd		*raw_commands;
	size_t			len;
}		t_raw_line;

typedef struct s_shell
{
	unsigned char	last_return_code;
	char			**envp;
	char			*files_to_delete;
}		t_shell;

int			file_exists(char *file_path);
char		*get_from_path(char *filename, char *envp[]);
char		*get_envp(char *key, char *envp[]);

#endif