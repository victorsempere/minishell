/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:15:50 by visv              #+#    #+#             */
/*   Updated: 2021/05/16 18:33:40 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_redirection(t_abs_struct *base, char *i)
{
	int		redirected;
	int		found_redirection;

	found_redirection = 0;
	redirected = 0;
	if (ft_output_add_redirection(base, i, &redirected))
		found_redirection = 1;
	if (!found_redirection && ft_output_redirection(i, &redirected))
		found_redirection = 1;
	if (!found_redirection && ft_input_redirection(i, &redirected))
		found_redirection = 1;
	if (found_redirection)
	{
		if (redirected)
			return (redirected);
		else
			return (-1);
	}
	return (0);
}

int	set_redirections(t_abs_struct *base, t_process *p)
{
	char	**i;
	int		redirOk;

	if (!p || !p->argv || !ft_extract_redirections_from_argv(p))
		return (1);
	i = p->redirs;
	while (i && *i)
	{
		redirOk = set_redirection(base, *i);
		if (redirOk < 0)
			return (0);
		i++;
	}
	return (1);
}

int	field_contains_redirs(char *field)
{
	return (ft_strstr(field, "<") || ft_strstr(field, ">>")
		|| ft_strstr(field, ">"));
}
