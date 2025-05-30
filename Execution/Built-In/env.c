/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:47:34 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/15 19:37:38 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

void	b_env(char **envp)
{
	int	i;

	if (!envp || !envp[0])
	{
		ft_putstr_fd("env: No environment variables found.\n", 2);
		g_last_return_code = 1;
	}
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
