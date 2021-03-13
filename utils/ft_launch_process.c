/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:19 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:18:20 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_execute_absolute_shell_command(t_abs_struct *base,
	t_process *p)
{
	if (execve(p->argv[0], p->argv, base->env) && errno == EACCES)
		p->status = 126;
	p->completed = 1;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
}

static void		ft_execute_relative_shell_command(t_abs_struct *base,
	t_process *p)
{
	char		*path;
	char		*tmp;

	if (!(path = getcwd(0, 0)))
		return ;
	tmp = ft_strjoin(path, p->argv[0] + 1);
	free(path);
	path = tmp;
	ft_execute_absolute_shell_command(base, p);
	free(path);
}

static void		ft_execute_shell_command_using_path(t_abs_struct *base,
	t_process *p)
{
	struct stat	statbuf;
	char		*paths;
	char		*path;
	char		*tmp;
	char		*orig_path;
	
	paths = ft_getenv(base->env, "PATH");
	orig_path = *p->argv;
	paths += 5;
	while ((path = ft_split_shell_by(&paths, ":")))
	{
		tmp = ft_strlcat_paths(path, orig_path);
		*p->argv = tmp;
		free(path);
		if (!stat(*p->argv, &statbuf)/* &&
			(statbuf.st_mode & __S_IFMT) == __S_IFREG*/)  //Aqui comente para hacer prueba
		{
			if (**p->argv == '/' || !ft_strncmp(*p->argv, "\"/", 2))
				ft_execute_absolute_shell_command(base, p);
			else
				ft_execute_relative_shell_command(base, p);
		}
		free(*p->argv);
		*p->argv = orig_path;
	}
	ft_putstr_fd(*p->argv, STDERR_FILENO);
	ft_putstr_fd(": not found command\n", STDERR_FILENO);
	p->completed = 1;
	p->status = 1;
}

void            ft_launch_process(t_abs_struct *base, t_process *current)
{
	if ((current->status = ft_set_default_signals()))
		return ;
	current->status = set_redirections(base, current);
	if (current->status)
		return ;
	if (*current->argv[0] == '/')
		ft_execute_absolute_shell_command(base, current);
	else if (*current->argv[0] == '.')
		ft_execute_relative_shell_command(base, current);
	else
		ft_execute_shell_command_using_path(base, current);
}
