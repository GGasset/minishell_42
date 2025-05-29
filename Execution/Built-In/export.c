/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:27:10 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/29 14:17:38 by apaz-pri         ###   ########.fr       */
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

void	update_envp(t_shell *shell, char *var)
{
	int		i;
	char	*key;
	size_t	len;

	len = ft_strchr(var, '=') - var;
	key = ft_substr(var, 0, len);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, len) == 0
			&& shell->envp[i][len] == '=')
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup(var);
			free(key);
			return ;
		}
		i++;
	}
	free(key);
	shell->envp = ft_realloc(shell->envp, sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2), 1);
	shell->envp[i] = ft_strdup(var);
	shell->envp[i + 1] = NULL;
}

static void	print_sort(t_exe exe)
{
	int	*index;
	int	i;
	int	j;
	int	counter;

	i = -1;
	index = ft_calloc(ft_get_split_count(exe.shell->envp), sizeof(int));
	while (exe.shell->envp[++i])
	{
		counter = 0;
		j = -1;
		while (exe.shell->envp[++j])
			if (ft_strcmp(exe.shell->envp[i], exe.shell->envp[j]) > 0)
				counter++;
		index[counter] = i;
	}
	i = 0;
	while (i < (int)ft_get_split_count(exe.shell->envp))
	{
		printf("%s\n", exe.shell->envp[index[i]]);
		i++;
	}
	free(index);
}

void	b_export(t_exe exe, int j)
{
	int	i;

	if (!exe.commands[j].argv[1])
	{
		i = 0;
		print_sort(exe);
		g_last_return_code = 0;
	}
	i = 1;
	while (exe.commands[j].argv[i])
	{
		if (!is_valid_identifier(exe.commands[j].argv[i]))
			g_last_return_code = 1;
		else
			update_envp(exe.shell, exe.commands[j].argv[i]);
		i++;
	}
}
