/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_prep2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:21:18 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/15 19:35:21 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

void	core_dump(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_last_return_code = 131;
	}
}