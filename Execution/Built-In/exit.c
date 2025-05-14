/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:02:48 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/14 12:56:11 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

void	b_exit(t_exe exe)
{
	if (exe.command_count == 1)
		printf("exit\n");
	exit_call(exe.shell, NULL, &exe, 0);
}
