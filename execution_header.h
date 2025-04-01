/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:35:57 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/01 18:25:39 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_HEADER_H
# define EXECUTION_HEADER_H

# include "common_header.h"

enum e_builtin
{
	not_builtin,
	echo,
	cd,
	pwd,
	export_b,
	unset,
	env,
	exit_b
};

typedef struct s_cmd
{
	int				err;
	char			*path;
	char			**argv;
	int				input_fd;
	int				output_fd;
	pid_t			pid;
	enum e_builtin	is_builtin;
}		t_cmd;

typedef struct s_exe
{
	t_cmd	*commands;
	size_t	command_count;
}		t_exe;

t_exe	prepare(t_raw_line raw_commands);
void	execute(t_exe commands);
void	stop_execution(t_exe commands, int sig);
void	free_execution_env(t_exe exe);

#endif
