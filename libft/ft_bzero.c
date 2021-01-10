/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:14:31 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:14:36 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_bzero(void *s, size_t n)
{
	char	*cs;
	size_t	i;

	cs = (char *)s;
	i = 0;
	while (i < n)
	{
		cs[i] = 0;
		i++;
	}
}
