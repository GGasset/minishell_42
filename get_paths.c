/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-17 12:59:31 by ggasset-          #+#    #+#             */
/*   Updated: 2025-04-17 12:59:31 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

char	*get_user_home(t_shell *shell)
{
	char	*out;
	
	out = get_envp("HOME", shell->envp);
	if (out)
		return (ft_strdup(out));
	out = get_envp("USER", shell->envp);
	if (!out)
		return (0);
	out = ft_strjoin("/home/", out);
	out = ft_strjoin_free(out, "/", TRUE, FALSE);
	return (out);
}

char	*get_pwd(t_shell *shell)
{
	return (ft_strjoin(get_envp("PWD", shell->envp), "/"));
}
