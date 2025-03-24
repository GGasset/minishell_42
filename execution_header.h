/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:35:57 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/24 14:36:18 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_HEADER_H
# define EXECUTION_HEADER_H

# include "common_header.h"

/*enum builtin_type
{
	command,
	echo,
	cd,
	pwd,
	export_b,
	unset,
	env,
	exit_b
};*/

typedef struct s_operator
{
	/*
	# Cases:
	- (<)
		* fd of file opened in RDONLY mode
		* Added to prev operator
		* Does not use pipe
	- (>)
		* fd of file opened in WRONLY and trucated
		* Added to next operator
		* Does not use pipe
	- (<<) 
		* fd of dupped command stdin
		* Added to prev operator
		* 
	- (>>)
		* fd of file opended in APPEND mode
		* Added to next operator
		* Does not use pipe
	- (|)
		* fd of next stdin program dupped fd
		* Added to both operators
		* uses pipe
	*/
	int					fd;
	int					pipe[2];
	enum e_operators	type;
}		t_operator;

typedef struct s_cmd
{
	char		*path;
	char		**argv;

	/*
	# Used with:
		1) <
		2) <<
		3) |
	### Nullable
	* Redirects stdin
	*/
	t_operator	*prev_operator;

	/*
	# Used with:
		1) >
		2) >>
		3) |
	### Nullable
	* Redirects stdout
	*/
	t_operator	*next_operator;
}		t_cmd;

typedef struct s_exe
{
	t_cmd	*commands;
	size_t	command_count;
}		t_exe;

#endif
