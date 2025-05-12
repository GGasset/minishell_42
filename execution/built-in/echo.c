/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:56:29 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/04/21 13:38:00 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_header.h"

/*
	2- Comprobar si la bash acepta el -n en cualquier lado 
		si lo acepta esta funcion es un mojon
*/
void	b_echo(t_cmd cmd)
{
	int	i;
	int	parameter;

	i = 1;
	parameter = 0;
	while (cmd.argv[i] && ft_strcmp(cmd.argv[i], "-n") == 0)
	{
		parameter = 1;
		i++;
	}
	while (cmd.argv[i])
	{
		printf("%s", cmd.argv[i]);
		if (cmd.argv[i+1] && cmd.argv[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (parameter == 0)
		printf("\n");
}