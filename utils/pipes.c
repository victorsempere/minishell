/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:12:45 by visv              #+#    #+#             */
/*   Updated: 2021/03/31 12:06:54 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_configure_pipes(t_abs_struct *base,
	t_process *current)
{
	if (current->next)
	{
		if (pipe(current->pipe) < 0)
			ft_exit_minishell(base, errno);
	}
	else
	{
		current->pipe[STDIN_FILENO] = -1;
		current->pipe[STDOUT_FILENO] = -1;
	}
}

void	ft_close_pipes(t_files_fd fds, t_process *previous,
	t_process *current)
{
	if (previous)
	{
		if (previous->pipe[STDIN_FILENO] > -1)
		{
			close(previous->pipe[STDIN_FILENO]);
			dup2(fds.infile, STDIN_FILENO);
		}
	}
	if (current->pipe[STDOUT_FILENO] > -1)
	{
		close(current->pipe[STDOUT_FILENO]);
		dup2(fds.outfile, STDOUT_FILENO);
	}
}

void	ft_set_pipes(t_process *previous, t_process *current)
{
	if (previous && previous->pipe[STDIN_FILENO] > -1)
		dup2(previous->pipe[STDIN_FILENO], STDIN_FILENO);
	if (current->pipe[STDOUT_FILENO] > -1)
		dup2(current->pipe[STDOUT_FILENO], STDOUT_FILENO);
}