/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:27:09 by meelma            #+#    #+#             */
/*   Updated: 2025/11/20 15:29:59 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static t_shell	**get_shell_ptr_addr(void)
{
	static t_shell	*sh;

	sh = NULL;
	return (&sh);
}

void	set_shell_ptr(t_shell *sh)
{
	t_shell	**ptr;

	ptr = get_shell_ptr_addr();
	*ptr = sh;
}

void	handle_sigint(int signo)
{
	t_shell	*sh;

	g_signal = signo;
	sh = *get_shell_ptr_addr();
	if (sh)
	sh->last_status = 130;
	write(1, "\nminishell> ", 13);
}
