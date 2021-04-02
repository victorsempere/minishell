/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:45:34 by acortes-          #+#    #+#             */
/*   Updated: 2021/03/31 12:07:17 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcdup(const char *s1, int c)
{
	int		i;
	char	*str;
	char	car;

	i = 0;
	car = (char)c;
	while (s1[i] != car && s1[i] != '\0')
		i++;
	str = malloc(i + 1 * sizeof(char));
	str[i] = '\0';
	if (str == NULL)
	{
		return (NULL);
	}
	while (i-- > 0)
		str[i] = s1[i];
	return (str);
}
