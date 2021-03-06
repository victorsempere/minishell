/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:37 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 15:47:09 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*ft_build_processes(char *cmd)
{
	t_process		*procs;
	t_process		*last_proc;
	char			*proc_cmd;

	procs = 0;
	last_proc = 0;
	proc_cmd = ft_split_shell_by(&cmd, "|");
	while (proc_cmd)
	{
		if (!procs)
		{
			procs = ft_build_process(proc_cmd);
			last_proc = procs;
		}
		else
		{
			last_proc->next = ft_build_process(proc_cmd);
			last_proc->next->prev = last_proc;
			last_proc = last_proc->next;
		}
		free(proc_cmd);
		proc_cmd = ft_split_shell_by(&cmd, "|");
	}
	return (procs);
}
