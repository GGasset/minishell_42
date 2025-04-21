/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:13:38 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/03 20:35:22 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_HEADER_H
# define COMMON_HEADER_H

# include <stddef.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

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

int		is_e_operator(int op);
int		is_redirect_operator(int op);
int		is_input_e_operator(int op);
int		is_output_e_operator(int op);

//* * Not used for pipes, 
// pipes will be created according to the number of commands
//
//* * Redirections have a higher priority than pipes
//*	*	* Meaning that when both pipe and redirect (i.e. >) are present command 
// will be dup'ed to redirect
/* ## Tests
echo "Hola" > out | <infile cat > out2
echo "Hola" > out | <infile cat > out2 | <infile1 cat > out3 | <infile2 cat
cat | cat | cat < parsing_header.h

*/
typedef struct t_raw_redirect
{
	char				*file;
	enum e_operators	type;
}		t_raw_redirect;

// Input and output _redirect are nullable
typedef struct s_raw_cmd
{
	char			*file;
	char			**argv;
	t_raw_redirect	*input_redirect;
	t_raw_redirect	*output_redirect;
}		t_raw_cmd;

typedef struct s_raw_line
{
	t_raw_cmd		*raw_commands;
	size_t			len;
}		t_raw_line;

void	free_raw_line(t_raw_line *line, int free_line);

// tmp_files are separated by '|' character
typedef struct s_shell
{
	char			**envp;
	char			*tmp_files;
}		t_shell;
void	remove_tmp_files(t_shell *shell);

int		file_exists(char *file_path);
char	*get_from_path(char *filename, char *envp[]);
char	*get_envp(char *key, char *envp[]);

// Checks for errors
// accepts relative routes, with pwd in shell TODO
// checks for missing pwd TODO
// Creates directories TODO
void	create_empty_file(char *path, t_shell *shell);

// If has filename is set to 0, everything will be considered a directory name
void	create_directory(char *path, int has_filename);

// If it fails to get HOME var, tries /home/$USER/, else returns 0
char	*get_user_home(t_shell *shell);
char	*get_pwd(t_shell *shell);

#endif