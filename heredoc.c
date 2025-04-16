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

char	*do_heredoc(char *delimiter, size_t i)
{
	char	*path;

	
	if (access(path, F_OK) || !access(path, W_OK))
		return (path);
}
