/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_release_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:29 by visv              #+#    #+#             */
/*   Updated: 2021/05/01 16:28:52 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_release_base(t_abs_struct *base)
{
	if (!base)
		return ;
	if (base->input)
		free(base->input);
	ft_array_release(base->env);
	base->parse_string = 0;
	if (base->last_history_command)
		free(base->last_history_command);
	ft_release_jobs(base->first_job);
	ft_array_release(base->history);
	base->first_job = 0;
	return ;
}
