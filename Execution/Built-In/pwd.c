/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:56:24 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/15 19:37:55 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

int	b_pwd(void)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	if (ft_strlen(pwd) > 0)
		printf("%s\n", pwd);
	else
		g_last_return_code = 1;
	return (0);
}
