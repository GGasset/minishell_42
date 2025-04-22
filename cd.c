/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:14:16 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/04/22 19:33:24 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

/*
	cd libft
	cd ../algo
	cd /tmp

	1- Comprobar que exista
	2- Si borran el directorio actual comprobar los casos en la bash
*/
void	b_cd(t_exe exe, int j)
{
	char *new_pwd;
	
	new_pwd = ft_strjoin("PWD=", exe.commands[j].argv[1]);
	update_envp(exe.shell, new_pwd);
}