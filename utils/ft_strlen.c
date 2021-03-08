/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:32:00 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:32:03 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && *(s + i) != '\0')
		i++;
	return (i);
}
