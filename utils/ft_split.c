/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:25:59 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 14:09:58 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	total_words(char const *s1, char c)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	while (s1[n])
	{
		if (s1[n] != c)
			j++;
		while (s1[n + 1] && s1[n] != c)
			n++;
		n++;
	}
	return (j);
}

int	len_of_word(const char *str, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (str[i] == c)
		i++;
	while (str[i] && str[i] != c)
	{
		word++;
		i++;
	}
	return (word);
}

char	**ft_split_key_value_pair(char const *s, char c)
{
	char	**key_value;
	int		len;

	if (!s || !ft_strchr(s, c))
		return (0);
	key_value = ft_calloc(3, sizeof(char *));
	if (!key_value)
		return (0);
	len = ft_strchr(s, c) - s;
	*key_value = ft_calloc(len + 1, sizeof(char));
	if (!(*key_value))
	{
		ft_array_release(key_value);
		return (0);
	}
	*(key_value + 1) = ft_calloc(ft_strlen(s) - len, sizeof(char));
	if (!*(key_value + 1))
	{
		ft_array_release(key_value);
		return (0);
	}
	ft_memcpy(*key_value, s, len);
	ft_memcpy(*(key_value + 1), s + len + 1, ft_strlen(s) - len - 1);
	return (key_value);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		n;
	int		j;

	i = 0;
	n = 0;
	j = 0;
	str = malloc(sizeof(char *) * (1 + total_words(s, c)));
	if (!s || !(str))
		return (NULL);
	while (i < total_words(s, c))
	{
		j = 0;
		str[i] = malloc(sizeof(char) * (1 + len_of_word(&s[n], c)));
		if (!(str[i]))
			return (NULL);
		while (s[n] == c)
			n++;
		while (s[n] != c && s[n])
			str[i][j++] = s[n++];
		str[i++][j] = '\0';
	}
	str[i] = NULL;
	return (str);
}
