/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 10:16:05 by ggasset-          #+#    #+#             */
/*   Updated: 2025-04-21 10:16:05 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"
#include "execution_header.h"

unsigned char	g_last_return_code = 0;

static int	setup()
{
	return (0);
}

static char	*readline_abstraction(t_shell *shell)
{
	char	*out;
	char	*prompt;

	prompt = ft_strdup(line_prompt);
	if (get_envp("USER", shell->envp))
		prompt = ft_strjoin_free(prompt, get_envp("USER", shell->envp), 1, 0);
	if (get_envp("PWD", shell->envp))
	{
		prompt = ft_strjoin_free(prompt, ":", TRUE, FALSE);
		prompt = ft_strjoin_free(prompt, get_envp("PWD", shell->envp), 1, 0);
	}
	out = readline(prompt);
	free(prompt);
	return (out);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;
	int		err;
	char	*line;

	err = 0;
	shell.envp = envp;
	if (setup())
		return (errno);
	while (TRUE)
	{
		line = readline_abstraction(&shell);
		free(line);
	}
}
