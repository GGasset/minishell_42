/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:47:55 by ggasset-          #+#    #+#             */
/*   Updated: 2025/05/12 19:31:06 by apaz-pri         ###   ########.fr       */
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
	out = ft_realloc(argv, sizeof(char *) * len, sizeof(char *) * (len + 1),
			TRUE);
	len++;
	if (out)
		out[len - 2] = ft_strdup_free(s, free_s);
	return (out);
}

// i is the start of the word after the operator
// just let the thing do the thing
// free your stuff
static void	set_redirect(char *w, t_raw_cmd *cmd, int op, t_shell *s)
{
	t_raw_redirect	**redirect;

	if (!w || !is_e_operator(op))
		return ;
	if (is_input_e_operator(op) && !get_access(w, TRUE, op, &cmd->err))
		redirect = &cmd->input_redirect;
	else if (is_output_e_operator(op) && !get_access(w, FALSE, op, &cmd->err))
		redirect = &cmd->output_redirect;
	else
		return ;
	if (*redirect)
	{
		free(redirect[0]->file);
		free(*redirect);
	}
	*redirect = malloc(sizeof(t_raw_redirect));
	if (!*redirect)
		return ;
	if (op == stdin_delimiter)
		w = do_heredoc(w, s);
	(*redirect)->file = ft_strdup(w);
	if (is_output_e_operator(op) && !cmd->err)
		create_empty_file((*redirect)->file, s, op == stdout_redirect);
	(*redirect)->type = op - (op == stdin_delimiter);
}

static void	set_file(t_raw_cmd *out, char *tmp_s, char current_op)
{
	int		contains_file;

	if (tmp_s && !is_e_operator(current_op))
	{
		contains_file = out->file != 0;
		if (!contains_file)
			out->file = ft_strdup_free(tmp_s, FALSE);
		out->argv = argv_append(out->argv, tmp_s, FALSE);
	}
}

static t_raw_cmd	tokenize_cmd(char *cmd, int *err, t_shell *shell)
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
		tmp_s = shell_get_word(cmd, i, &operator, err);
		tmp_s = remove_outer_quotes(tmp_s, TRUE);
		*err = *err || (current_op && !tmp_s);
		set_redirect(tmp_s, &out, current_op, shell);
		set_file(&out, tmp_s, current_op);
		i = get_next_word_start_i(cmd, i);
		free(tmp_s);
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
	out.rwcmds = malloc(sizeof(t_raw_cmd) * out.len);
	ft_bzero(out.rwcmds, sizeof(t_raw_cmd) * out.len);
	i = 0;
	while (err && !*err && commands && out.rwcmds && commands[i])
	{
		if (!commands[i][0])
		{
			*err = out.len != 1;
			break ;
		}
		out.rwcmds[i] = tokenize_cmd(commands[i], err, shell);
		if (!out.rwcmds[i].argv)
			out.rwcmds[i].argv = ft_calloc(1, sizeof(char *));
		i++;
	}
	ft_free_splitted(commands);
	if ((err && *err) || (!commands))
		free_raw_line(&out, FALSE);
	return (out);
}
