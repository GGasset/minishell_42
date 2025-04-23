/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:14:16 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/04/23 19:31:28 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

/*
	cd libft
	cd ../algo
	cd /tmp
	cd
	cd -
*/
void	b_cd(t_exe exe, int j)
{
	char *path;
	char *new_pwd;
	char cwd[PATH_MAX];

	if (!exe.commands[j].argv[1])
	{
		path = get_envp("HOME", exe.shell->envp);
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return ;
		}
	}
	else
		path = exe.commands[j].argv[1];
	if (chdir(exe.commands[j].argv[1]) == -1)
		printf("%s\n", strerror(errno));
	if (getcwd(cwd, PATH_MAX))
	{
		new_pwd = ft_strjoin("PWD=", cwd);
		update_pwd(exe.shell, new_pwd);
		free(new_pwd);
	}
}