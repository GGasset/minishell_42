/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:09:42 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/22 12:59:53 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

void c_error(t_exe exe, size_t i)
{
    struct stat fs;

    stat(exe.commands[i].path, &fs);
    if (errno == ENOENT)
    {
        ft_printf_fd(2, "mini: %s: command not found\n", exe.commands[i].argv[0]);
        exit(127);
    }
    else if (errno == EACCES)
    {
        ft_printf_fd(2, "mini: %s: Permission denied\n", exe.commands[i].argv[0]);
        exit(126);
    }
	else if (S_ISDIR(fs.st_mode))
	{
		ft_printf_fd(2, "mini: %s: Is a directory\n", exe.commands[i].argv[0]);
		exit(126);
	}
    else
        exit(1);
}