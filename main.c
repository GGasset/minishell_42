/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:16:05 by ggasset-          #+#    #+#             */
/*   Updated: 2025/05/12 18:51:26 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"
#include "parsing_header.h"

unsigned char	g_last_return_code = 0;

static int	setup(void)
{
	prompt_signal_behaviour();
	return (0);
}

static char	*readline_abstraction(t_shell *shell)
{
	char	*out;
	char	*prompt;

	prompt = ft_strdup(LINE_PROMPT);
	if (get_envp("USER", shell->envp))
		prompt = ft_strjoin_free(prompt, get_envp("USER", shell->envp), 1, 0);
	if (get_envp("PWD", shell->envp))
	{
		prompt = ft_strjoin_free(prompt, ":", TRUE, FALSE);
		prompt = ft_strjoin_free(prompt, get_envp("PWD", shell->envp), 1, 0);
	}
	prompt = ft_strjoin_free(prompt, PROMPT_END, TRUE, FALSE);
	rl_on_new_line();
	out = readline(prompt);
	add_history(out);
	free(prompt);
	return (out);
}

static void	readline_loop(t_shell *shell)
{
	t_raw_line	tokenized;
	t_exe		exe_struct;
	int			err;
	char		*line;

	while (TRUE)
	{
		prompt_signal_behaviour();
		err = 0;
		line = readline_abstraction(shell);
		cntr_d(line, tokenized, exe_struct);
		tokenized = parse_input(line, &err, shell);
		if (err)
		{
			write(2, PARSE_ERR, ft_strlen(PARSE_ERR));
			free(line);
			continue ;
		}
		free(line);
		if (tokenized.len)
			command(exe_struct, tokenized, shell);
		remove_tmp_files(shell);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	if (envp)
		shell.envp = ft_splitdup(envp);
	else
		shell.envp = ft_calloc(1, sizeof(char *));
	if (setup())
		return (errno);
	readline_loop(&shell);
}
