/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:08:28 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/27 19:07:02 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_header.h"

enum e_states	get_state(enum e_operators op)
{
	if (op == 0 || op == '|')
		return (command_parsing);
	if (op == '<' || op == '<' + 1)
		return (input_parsing);
	if (op == '>' || op == '>' + 1)
		return (output_parsing);
	return (state_err);
}

int	is_compatible(enum e_states prev, enum e_states next)
{
	if (next == state_err || prev == state_err)
		return (FALSE);
	if (next == input_parsing)
		return (FALSE);
	if (prev == output_parsing)
		return (FALSE);
	return (TRUE);
}
