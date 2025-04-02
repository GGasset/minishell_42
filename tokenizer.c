/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:47:55 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/02 19:14:44 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

// i is the start of the word after the operator
// just let the thing do the thing
// free your stuff
static void	set_redirect(char *word, t_raw_cmd *cmd, int e_operator)
{
	t_raw_redirect	**redirect;

	if (is_input_e_operator(e_operator))
		redirect = &cmd->input_redirect;
	else if (is_output_e_operator(e_operator))
		redirect = &cmd->output_redirect;
	else
		return ;
	if (*redirect)
	{
		free(*redirect);
		*redirect = 0;
	}
	*redirect = malloc(sizeof(t_raw_redirect));
	if (!*redirect)
		return ;
	(*redirect)->type = e_operator;
	(*redirect)->file = ft_strdup(word);
}

t_raw_cmd	tokenize_command(char *command, int *err)
{
	t_raw_cmd	out;
	char		operator;
	char		current_op;
	char		*tmp_s;
	size_t		i;
	
	ft_bzero(&out, sizeof(out));
	current_op = 0;
	i = 0;
	while (operator && err && !*err)
	{
		tmp_s = shell_get_word(command, i, &operator);
		*err = is_e_operator(current_op) && !tmp_s; 
		if (is_e_operator(current_op) && *err)
			set_redirect(tmp_s, &out, current_op);
		else if (tmp_s)
		{
			if (!out.file)
				out.file = ft_strdup(tmp_s);
			out.argv = argv_append(out.argv, tmp_s, FALSE);
		}
		current_op = operator;
		free(tmp_s);
	}
	return (out);
}

t_raw_line	tokenize_line(char *line, int *err)
{
	char		**commands;
	t_raw_line	out;
	size_t		i;

	commands = minishell_split(line, '|');
	out.len = ft_get_split_count(commands);
	out.raw_commands = malloc(sizeof(t_raw_cmd) * out.len);
	ft_bzero(out.raw_commands, sizeof(t_raw_cmd) * out.len);
	i = 0;
	while (err && !*err && commands && out.raw_commands && commands[i])
	{
		out.raw_commands[i] = tokenize_command(commands[i], err);
		i++;
	}
	ft_free_splitted(commands);
	if ((err && *err) || (!commands))
		free_raw_line(out);
	return (out);
}
