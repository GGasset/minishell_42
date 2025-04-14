/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:47:55 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/03 18:42:37 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

char	**argv_append(char **argv, char *s, int free_s)
{
	char	**out;
	size_t	len;

	len = ft_get_split_count(argv) + 1;
	if (!argv)
		argv = ft_calloc(1, sizeof(char *));
	out = ft_realloc(argv, sizeof(char *) * len,
		sizeof(char *) * (len + 1), TRUE);
	len++;
	if (out)
		out[len - 2] = ft_strdup_free(s, free_s);
	return (out);
}

// i is the start of the word after the operator
// just let the thing do the thing
// free your stuff
static void	set_redirect(char *word, t_raw_cmd *cmd, int e_operator, t_shell *s)
{
	t_raw_redirect	**redirect;

	if (!word)
		return ;
	if (is_input_e_operator(e_operator))
		redirect = &cmd->input_redirect;
	else if (is_output_e_operator(e_operator))
	{
		redirect = &cmd->output_redirect;
		create_empty_file(word, s);
	}
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

static void	set_file(t_raw_cmd *out, char *tmp_s, char current_op)
{
	if (tmp_s && !is_e_operator(current_op))
	{
		if (!out->argv)
			out->file = ft_strdup(tmp_s);
		out->argv = argv_append(out->argv, tmp_s, FALSE);
	}
	free(tmp_s);
}

static t_raw_cmd	tokenize_command(char *command, int *err, t_shell *shell)
{
	t_raw_cmd	out;
	char		operator;
	char		current_op;
	char		*tmp_s;
	size_t		i;

	ft_bzero(&out, sizeof(out));
	current_op = 0;
	operator = 0;
	i = 0;
	while (err && !*err)
	{
		tmp_s = shell_get_word(command, i, &operator);
		*err = current_op && !tmp_s;
		set_redirect(tmp_s, &out, current_op, shell);
		set_file(&out, tmp_s, current_op);
		i = get_next_word_start_i(command, i);
		if (!operator)
			break ;
		current_op = operator;
	}
	return (out);
}

t_raw_line	tokenize_line(char *line, int *err, t_shell *shell)
{
	char		**commands;
	t_raw_line	out;
	size_t		i;

	commands = shell_split(line, '|');
	out.len = ft_get_split_count(commands);
	out.raw_commands = malloc(sizeof(t_raw_cmd) * out.len);
	ft_bzero(out.raw_commands, sizeof(t_raw_cmd) * out.len);
	i = 0;
	while (err && !*err && commands && out.raw_commands && commands[i])
	{
		if (!commands[i][0])
		{
			*err = 1;
			break ;
		}
		out.raw_commands[i] = tokenize_command(commands[i], err, shell);
		i++;
	}
	ft_free_splitted(commands);
	if ((err && *err) || (!commands))
		free_raw_line(&out, FALSE);
	return (out);
}
