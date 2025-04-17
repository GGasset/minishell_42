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

#include "parsing_header.h"

static int	handle_nl(char *d, char **buff, ssize_t nline_i, int fd)
{
	if (!*buff)
		return (TRUE);
	if (!ft_strncmp(d, *buff, nline_i))
	{
		free(*buff);
		*buff = 0;
		return (TRUE);
	}
	write(fd, *buff, nline_i + 1);
	free(*buff);
	buff = ft_calloc(1, 1);
	printf("%s", heredoc_prompt);
	return (FALSE);
}

static void	heredoc_loop(char *delimiter, int write_fd)
{
	char	*buff;
	size_t	buff_len;
	char	tmp;
	ssize_t	nline_i;

	buff_len = 0;
	buff = ft_calloc(1, 1);
	printf("%s", heredoc_prompt);
	while (buff && delimiter && write_fd != -1 && read(0, &tmp, 1) > 0)
	{
		buff = ft_realloc(buff, buff_len + 1, buff_len + 2, TRUE);
		buff_len++;
		buff[buff_len - 1] = tmp;
		nline_i = ft_strchr_i(buff, '\n');
		if (nline_i != -1 && handle_nl(delimiter, &buff, nline_i, write_fd))
			break ;
	}
}

char	*do_heredoc(char *delimiter, size_t i, t_shell *shell)
{
	char	*path;
	int		fd;

	path = get_user_home(shell);
	if (!path)
		path = get_pwd(shell);
	if (!path)
		path = ft_strdup("/tmp/");
	path = ft_strjoin_free(path, ".minishell_heredoc_@&xfb$@_", TRUE, FALSE);
	path = ft_strjoin_free(path, ft_itoa((int)i), TRUE, TRUE);
	if (access(path, F_OK) && !access(path, W_OK))
		return (path);
	if (!shell->tmp_files)
		shell->tmp_files = ft_calloc(1, 1);
	else
		shell->tmp_files = ft_strjoin_free(shell->tmp_files, "|",
			TRUE, FALSE);
	shell->tmp_files = ft_strjoin_free(shell->tmp_files, path, TRUE, FALSE);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		return (path);
	heredoc_loop(delimiter, fd);
	close(fd);
	return (path);
}
