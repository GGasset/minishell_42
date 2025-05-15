/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:45:57 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/03 20:31:50 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

void	create_empty_file(char *path, t_shell *shell, int *err)
{
	int	fd;

	shell = 0;
	if (!access(path, F_OK) && access(path, W_OK))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		*err = TRUE;
		return ;
	}
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("ERROR\n", 2);
		*err = TRUE;
		return ;
	}
	close(fd);
}
