/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:27:10 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/04/22 19:08:14 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_header.h"

/*
	export KEY=VALOR
	❌ export KEY = VALOR
*/
static int	is_valid_identifier(char *str)
{
    int	i;

    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void	update_envp(t_shell *shell, char *var)
{
    int		i;
    char	*key;
    size_t	len;

    len = ft_strchr(var, '=') - var;
    key = ft_substr(var, 0, len);
    i = 0;
    while (shell->envp[i])
    {
        if (ft_strncmp(shell->envp[i], key, len) == 0 && shell->envp[i][len] == '=')
        {
            free(shell->envp[i]);
            shell->envp[i] = ft_strdup(var);
            free(key);
            return;
        }
        i++;
    }
    free(key);
    shell->envp = ft_realloc(shell->envp, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2), 0); //TODO: duplicar envp
    shell->envp[i] = ft_strdup(var);
    shell->envp[i + 1] = NULL;
}

void	b_export(t_exe exe, int j)
{
    int	i;

    if (!exe.commands[j].argv[1])
    {
        for (i = 0; exe.shell->envp[i]; i++)
            printf("%s\n", exe.shell->envp[i]);
        return;
    }
    i = 1;
    while (exe.commands[j].argv[i])
    {
        if (!is_valid_identifier(exe.commands[j].argv[i]))
            return ;
        else
            update_envp(exe.shell, exe.commands[j].argv[i]);
        i++;
    }
}