/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:14:16 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/14 12:55:43 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

/*
	✅ cd libft
	✅ cd ../algo
	✅ cd /tmp
	✅ cd
	✅ cd -
*/
void	change_old_pwd(t_exe exe, char *cwd)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", cwd);
	update_envp(exe.shell, old_pwd);
	free(old_pwd);
}

void	change_new_pwd(t_exe exe, char *cwd)
{
	char	*new_pwd;

	new_pwd = ft_strjoin("PWD=", cwd);
	update_envp(exe.shell, new_pwd);
	free(new_pwd);
}

char	*check_home(t_exe exe, int j)
{
	char	*path;

	if (!exe.commands[j].argv[1])
	{
		path = get_envp("HOME", exe.shell->envp);
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else if (ft_strcmp(exe.commands[j].argv[1], "-") == 0)
	{
		path = get_envp("OLDPWD", exe.shell->envp);
		if (!path)
		{
			ft_putstr_fd("cd: No last directory\n", 2);
			return (NULL);
		}
	}
	else
		path = exe.commands[j].argv[1];
	return (path);
}

void	b_cd(t_exe exe, int j)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];

	path = check_home(exe, j);
	if (!path)
		return ;
	getcwd(old_cwd, PATH_MAX);
	if (chdir(path) == -1)
		printf("cd: %s\n", strerror(errno));
	if (getcwd(cwd, PATH_MAX))
	{
		change_new_pwd(exe, cwd);
		change_old_pwd(exe, old_cwd);
	}
}
