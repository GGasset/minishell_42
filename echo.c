/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:56:29 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/04/21 00:22:20 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_header.h"

/*
	1- Comprobar q argv con -n siempre tiene el tamaño de 2
	2- Comprobar si la bash acepta el -n en cualquier lado 
		si lo acepta esta funcion es un mojon porq no imprime
		los argumentos de antes del -n
*/
void	b_echo(t_exe cmd)
{
	int	i;
	int	parameter;

	i = 0;
	while (ft_strncmp(cmd.commands->argv[i], "-n", 2) && cmd.commands->argv[i])
	{
		parameter = 1;
		i++;
	}
	while (cmd.commands->argv[i])
	{
		printf("%s", cmd.commands->argv[i]);
		if (cmd.commands->argv[i+1] && cmd.commands->argv[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (parameter == 0)
		printf("\n");
}