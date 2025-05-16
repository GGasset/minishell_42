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

void	create_empty_file(char *path, t_shell *shell, int trunc)
{
	int	fd;

	shell = 0;
	if (!access(path, F_OK) && access(path, W_OK))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_last_return_code = 1;
		return ;
	}
	fd = open(path, O_WRONLY | (O_TRUNC && trunc) | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("ERROR\n", 2);
		return ;
	}
	close(fd);
}

int	get_access(char *path, int must_exist, int operator, int *out)
{
	int	output;
	int permission;

	if (operator == stdin_delimiter)
		return (0);
	permission = R_OK * is_input_e_operator(operator);
	permission += W_OK * is_output_e_operator(operator);
	output = 0;
	if ((must_exist && (access(path, F_OK) || access(path, permission))))
	{
		output = 1;
		if (out && *out)
			return (output);
		if (out)
			*out = 1;
		ft_putstr_fd(path, 2);
		if (must_exist && access(path, F_OK))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
	}
	return (output);
}
