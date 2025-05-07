/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:39 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/02 16:30:57 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_header.h"

int	is_e_operator(int op)
{
	return (is_redirect_operator(op) || op == pipe_op);
}

int	is_redirect_operator(int op)
{
	return (is_input_e_operator(op) || is_output_e_operator(op));
}

int	is_input_e_operator(int op)
{
	return (op == stdin_redirect || op == stdin_delimiter);
}

int	is_output_e_operator(int op)
{
	return (op == stdout_redirect || op == stdout_append);
}
