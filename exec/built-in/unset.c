/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:38:41 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/02 13:41:14 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

static int	find_env_index(char **envp, const char *key)
{
    int		i;
    size_t	len;

    len = ft_strlen(key);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

void	remove_env_var(t_shell *shell, int index)
{
    int		i;

    free(shell->envp[index]);
    i = index;
    while (shell->envp[i])
    {
        shell->envp[i] = shell->envp[i + 1];
        i++;
    }
}

void	b_unset(t_exe exe, int j)
{
    int		i;
    int		index;

    if (!exe.commands[j].argv[1])
        return ;
    i = 1;
    while (exe.commands[j].argv[i])
    {
        index = find_env_index(exe.shell->envp, exe.commands[j].argv[i]);
        if (index != -1)
            remove_env_var(exe.shell, index);
        i++;
    }
}