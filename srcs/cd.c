/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:24 by acortes-          #+#    #+#             */
/*   Updated: 2021/03/02 16:25:24 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_file_doesnt_exist(char *file)
{
	ft_putstr("\e[0mcd: ");
	if (file)
		ft_putstr(file);
	ft_putstr(": File or dir doesn't exist\n");
}

int				cd(abs_struct *base)
{
	char		*home;

	base->num_args = ft_count_words_until_separator(base->parseString, base->actual_argument);
	base->error = (base->num_args > 2 ? 1 : 0);
	if (base->error)
		ft_putstr("\e[0mcd: Too many arguments\n");
    else if (base->num_args > 1 && !ft_isempty(base->parseString[base->actual_argument + 1]))
		home = ft_get_absolute_path(base, base->parseString[base->actual_argument + 1]);
	else
	{
		base->error = !(home = ft_getenv(base->env, "HOME"));
		if (home)
			home = ft_get_absolute_path(base, home + 5);
		else
	        ft_putstr("\e[0mcd: HOME not defined\n");
	}
	if (!base->error)
	{
		base->error = chdir(home);
		if (base->error)
			print_file_doesnt_exist(home);
		free(home);
	}
    return (!base->error);
}
