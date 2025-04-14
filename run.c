/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:14 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/04/14 14:52:20 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"
#include "stdio.h"
#include "parsing_header.h"
#include "execution_header.h"

void	free2(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

char	**get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	}
	return (ft_split(envp[i] + 5, ':'));
}

char	*get_binary(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	**path;
	char	*binary;

	i = 0;
	path = get_path(envp);
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		binary = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(binary, F_OK) == 0)
		{
			free2(path);
			return (binary);
		}
		free(binary);
		i++;
	}
	free2(path);
	return (NULL);
}

/*
	Suponiendo que el punero de cmd->file siempre apunta a un comando
	SUponiendo que el puntero de cmd->argv son los argumentos del comando

	compruebo que no sea la ruta absoluta del binario
	Si no lo es, busco el binario en el path 

	y luego ejecuto el binario con los comandos
*/
void	execcommand(t_raw_cmd *cmd, char **envp)
{
	char	*binary;
	bool	full_path;

	if (access(cmd->file, F_OK) == 0)
	{
		binary = cmd->file;
		full_path = true;
	}
	else
		binary = get_binary_path(cmd->file, envp);
	execve(binary, cmd->argv, envp);
}

void    infile(int	*fd, char **envp, t_raw_line *cmd)
{
	int fd_in;

	fd_in = open(cmd->raw_commands->input_redirect->file, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error opening input file");
		return;
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd[0]);
	exec_command(envp, cmd->raw_commands);
}

int execpipex(t_raw_line *cmd, char **envp)
{
    int fd[2];


    (void)envp;
    printf("Comando a ejecutar -> %s\n", cmd->raw_commands->file);
    for (int i = 0; cmd->raw_commands->argv[i] != NULL; i++)
    {
        printf("Argumentos a ejecutar %s\n", cmd->raw_commands->argv[i]);
    }
    if (cmd->raw_commands->input_redirect)
        printf("Redirecciones de entrada -> %s\n", cmd->raw_commands->input_redirect->file);
    if (cmd->raw_commands->output_redirect)
        printf("Redirecciones de salida -> %s\n", cmd->raw_commands->output_redirect->file);
    return 0;
}