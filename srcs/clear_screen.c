/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:25:34 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 17:10:27 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_screen(void)
{
	ft_putstr("\e[0m\033[2J\033[1;1H");
	ft_putstr("\e[92m             |||------------------------------||| \n");
	ft_putstr("             |||------------------------------||| \n");
	ft_putstr("             |||------------------------------||| \n");
	ft_putstr("             |||           MINISHELL          ||| \n");
	ft_putstr("             |||------------------------------||| \e[0m\n\n\n");
}