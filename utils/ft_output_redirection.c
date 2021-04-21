/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:53:20 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:12:19 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_to_i_fd(int empty, char *fd)
{
	if (empty)
		return (STDOUT_FILENO);
	return (ft_atoi(fd));
}

int	assign_to_fd_helper(char c)
{
	if (c == '&')
		return (1);
	else
		return (0);
}

void	redirect_to_exit(t_abs_struct *base, int o_fd, int i_fd)
{
	if (o_fd < 0)
		ft_exit_minishell(base, errno);
	if (dup2(o_fd, i_fd) < 0)
		ft_exit_minishell(base, errno);
}

static int	apply_output_redirection(t_abs_struct *base, char *fd,
	char *right_side)
{
	int			i_fd;
	int			o_fd;
	int			empty;
	int			fd_help;
	char		*fd_file;

	empty = ft_isempty(fd);
	if (!ft_isinteger(fd) && !(empty))
		return (0);
	i_fd = assign_to_i_fd(empty, fd);
	fd_file = ft_trim(right_side);
	if (!(fd_file))
		return (1);
	if (!ft_strncmp(fd_file, "&-", 2))
	{
		free(fd_file);
		return (close(i_fd));
	}
	fd_help = assign_to_fd_helper(*fd_file);
	o_fd = open((fd_file + fd_help), O_CREAT | O_TRUNC | O_WRONLY, 0666);
	redirect_to_exit(base, o_fd, i_fd);
	if (*fd_file != '&')
		close(o_fd);
	free(fd_file);
	return (0);
}

int	ft_output_redirection(t_abs_struct *base, char *redir,
	int *redirected)
{
	char		*fd;
	int			found_redirection;

	found_redirection = 0;
	fd = 0;
	if (redir)
		fd = ft_split_shell_by(&redir, ">");
	if (redir && fd && *(redir - 1) == '>')
	{
		*redirected = apply_output_redirection(base, fd, redir);
		found_redirection = 1;
	}
	if (fd)
		free(fd);
	return (found_redirection);
}