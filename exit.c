/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:02:48 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/07 12:16:53 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

void	b_exit(t_exe exe)
{
	int	exit_code;

	exit_code = g_last_return_code;
	exit_call(exe.shell, NULL, &exe, exit_code);
}