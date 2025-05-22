/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:35:57 by ggasset-          #+#    #+#             */
/*   Updated: 2025/05/22 12:16:44 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_HEADER_H
# define EXECUTION_HEADER_H

# include "common_header.h"

enum				e_builtin
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
	pid_t			pid;
	int				err;
	char			*path;
	char			**argv;
	int				input_fd;
	int				output_fd;
	enum e_builtin	is_builtin;
}					t_cmd;

typedef struct s_exe
{
	t_cmd			*commands;
	t_shell			*shell;
	size_t			command_count;
}					t_exe;

// * Preparation *
t_exe				prepare(t_raw_line rwcmd, t_shell *shell);

// * Execution *
void				command(t_exe exe, t_raw_line raw, t_shell *shell);
void				e_run(t_exe exe);

// * Pipes *
void				p_run(t_cmd *cmd, t_exe exe, int **pipes, size_t idx);
void				p_create(int **pipes, t_exe exe);

// * Built-in *
void				b_run(t_exe exe, int j);
void				b_cd(t_exe exe, int i);
void				b_unset(t_exe exe, int j);
void				b_env(char **envp);
void				b_exit(t_exe exe, int j);
void				b_echo(t_cmd cmd);
void				b_export(t_exe exe, int i);
int					b_pwd(void);
int					is_builtin(char *cmd);

// * Utils *
void				update_envp(t_shell *shell, char *var);
void				free_execution_env(t_exe exe);
void				exit_call(t_shell *s, t_raw_line *lines, t_exe *structure,
						int code);
void				core_dump(int sig);

// * ERRORS *
void 				c_error(t_exe exe);
#endif
