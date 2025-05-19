/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:02:48 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/19 18:01:35 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	b_exit(t_exe exe, int j)
{
	int	exit_code;

	if (exe.command_count == 1)
		printf("exit\n");
	if (exe.commands[j].argv[1] && exe.commands[j].argv[2])
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		g_last_return_code = 1;
		return ;
	}
	if (exe.commands[j].argv[1])
	{
		if (!is_numeric(exe.commands[j].argv[1]))
		{
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				exe.commands[j].argv[1]);
			exit_code = 2;
		}
		else
			exit_code = ft_atoi(exe.commands[j].argv[1]);
	}
	else
		exit_code = 0;
	exit_call(exe.shell, NULL, &exe, exit_code);
}
