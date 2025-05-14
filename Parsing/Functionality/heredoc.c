/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-15 15:14:45 by ggasset-          #+#    #+#             */
/*   Updated: 2025-04-15 15:14:45 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"
#include "parsing_header.h"

static int	handle_nl(char *d, char **buff, size_t nline_i, int fd)
{
	if (!*buff)
		return (TRUE);
	if (!ft_strncmp(d, *buff, nline_i) && nline_i == ft_strlen(d))
	{
		free(*buff);
		*buff = 0;
		return (TRUE);
	}
	write(fd, *buff, nline_i + 1);
	free(*buff);
	*buff = ft_calloc(1, 1);
	write(1, HEREDOC_PROMPT, ft_strlen(HEREDOC_PROMPT));
	return (FALSE);
}

/*static void	heredoc_loop(char *delimiter, int write_fd)
{
	char	*buff;
	size_t	buff_len;
	char	tmp;
	ssize_t	nline_i;

	buff_len = 0;
	buff = ft_calloc(1, 1);
	write(1, HEREDOC_PROMPT, ft_strlen(HEREDOC_PROMPT));
	//printf("\n");
	while (buff && delimiter && write_fd != -1 && read(0, &tmp, 1) > 0)
	{
		//printf("%d\n", tmp);
		if (tmp == EOF)
		{
			free(buff);
			return ;
		}
		buff = ft_realloc(buff, buff_len + 1, buff_len + 2, TRUE);
		buff_len++;
		buff[buff_len - 1] = tmp;
		nline_i = ft_strchr_i(buff, '\n');
		if (nline_i != -1 && handle_nl(delimiter, &buff, nline_i, write_fd))
			break ;
		else if (nline_i != -1)
			buff_len = 0;
	}
}*/

static void	heredoc_loop(char *delimiter, int write_fd)
{
	char	*buff;
	int		_exit;

	signal(SIGINT, SIG_IGN);
	if (fork() > 0)
		wait(0);
	else
	{
		signal(SIGINT, heredoc_signal_handler);
		_exit = 0;
		while (!_exit && delimiter && write_fd > 0)
		{
			buff = readline(HEREDOC_PROMPT);
			if (!buff)
				break ;
			if (!ft_strncmp(buff, delimiter, -1))
				_exit = 1;
			buff = ft_strjoin_free(buff, "\n", TRUE, FALSE);
			if (!_exit)
				write(write_fd, buff, ft_strlen(buff));
			free(buff);
		}
		exit(0);
	}
	prompt_signal_behaviour();
}

char	*do_heredoc(char *delimiter, size_t i, t_shell *shell)
{
	char	*path;
	int		fd;

	path = ft_strdup(".heredoco");
	if (access(path, F_OK) && !access(path, W_OK))
		return (path);
	if (!shell->tmp_files)
		shell->tmp_files = ft_calloc(1, 1);
	else
		shell->tmp_files = ft_strjoin_free(shell->tmp_files, "|",
				TRUE, FALSE);
	shell->tmp_files = ft_strjoin_free(shell->tmp_files, path, TRUE, FALSE);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (path);
	heredoc_loop(delimiter, fd);
	close(fd);
	return (path);
}
