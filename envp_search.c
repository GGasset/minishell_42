/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:15:23 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/19 17:16:48 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

char	*get_envp(char *key, char *envp[])
{
	size_t	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], key, -2) == envp[i])
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (0);
}

int	file_exists(char *file_path)
{
	int		file_fd;

	if (!file_path)
		return (0);
	file_fd = open(file_path, O_RDONLY);
	if (file_fd != -1)
	{
		close(file_fd);
		return (1);
	}
	return (0);
}

static char	*search_in_path(char *filename, char **path)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin_free(tmp, filename, 1, 0);
		if (file_exists(tmp))
			return (tmp);
		free(tmp);
		i++;
	}
	return (0);
}

char	*get_from_path(char *filename, char *envp[])
{
	char	*path_raw;
	char	**path;
	char	*file_path;

	if (!filename)
		return (0);
	path_raw = get_envp("PATH", envp);
	if (!path_raw)
		return (0);
	path = ft_split(path_raw, ':');
	if (!path)
		return (0);
	file_path = search_in_path(filename, path);
	ft_free_splitted(path);
	return (file_path);
}
