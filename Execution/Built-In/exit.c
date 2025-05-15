/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:02:48 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/15 19:29:02 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

void	b_exit(t_exe exe, int j)
{
	int	i;

	i = j;
	if (exe.command_count == 1)
		printf("exit\n");
	exit_call(exe.shell, NULL, &exe, 0);
}
