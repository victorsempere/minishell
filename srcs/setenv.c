/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 19:03:21 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env_value(char **envp, char *env_value)
{
	char		*z[3];
	size_t		offset;

	if (!env_value)
		return (0);
	z[0] = ft_strchr(env_value, '=');
	if (!z[0]++)
		return (0);
	z[1] = 0;
	if (!ft_memcmp(z[0], "~/", 2))
		z[1] = ft_getenv(envp, "HOME");
	if (z[1])
		z[1] = z[1] + 5;
	z[2] = malloc(sizeof(char) * ((z[0] - env_value) \
		 + ft_strlen(z[1]) + ft_strlen(z[0]) + ft_check_home((z[1]))));
	if (!(z[2]))
		return (0);
	offset = z[0] - env_value;
	ft_memcpy(z[2], env_value, offset);
	if (z[1])
		ft_memcpy((z[2] + offset), z[1], ft_strlen(z[1]));
	offset += ft_strlen(z[1]);
	ft_memcpy(z[2] + offset, z[0] + (z[1] ? 1 : 0), \
	ft_strlen(z[0]) + (z[1] ? -1 : 0));
	*(z[2] + offset + ft_strlen(z[0]) + ft_check_home2(z[1])) = 0;
	return (z[2]);
}

static int	ft_add_line(char ***envp, int *elems, char *env_value)
{
	char		*expanded_value;
	char		**aux;
	int			x;

	expanded_value = expand_env_value(*envp, env_value);
	if (!expanded_value)
		return (1);
	x = 0;
	aux = malloc(sizeof(char *) * (*elems + 2));
	if (!(aux))
		return (0);
	while (x < *elems)
	{
		*(aux + x) = *((*envp) + x);
		*((*envp) + x) = 0;
		x++;
	}
	*(aux + x) = expanded_value;
	(*elems)++;
	aux[*elems] = NULL;
	if (*envp)
		free(*envp);
	*envp = aux;
	return (1);
}

static int	ft_search_env(char **env, char *key)
{
	int			pos;
	char		**tmp;
	size_t		key_len;

	key_len = ft_strlen(key);
	pos = 0;
	tmp = env;
	while (key_len && tmp && *tmp)
	{
		if (ft_strlen(*tmp) > key_len && !ft_memcmp(*tmp, key, key_len)
			&& *((*tmp) + key_len) == '=')
			return (pos);
		tmp++;
		pos++;
	}
	return (0);
}

static char	*ft_prepare_export(char *key, char *value)
{
	char		*adj;
	char		*tri;

	if (!key || !value)
		return (0);
	tri = malloc(sizeof(char));
	if (ft_isspace(*value))
		tri = ft_strdup("");
	else
		tri = ft_strdup(value);
	if (!tri)
		return (0);
	ft_remove_quotes(tri);
	adj = ft_calloc(ft_strlen(key) + 1 + ft_strlen(tri) + 1, sizeof(char));
	if (!(adj))
	{
		free(tri);
		return (0);
	}
	ft_memcpy(adj, key, ft_strlen(key));
	adj[ft_strlen(key)] = '=';
	ft_memcpy(adj + ft_strlen(key) + 1, tri, ft_strlen(tri));
	free(tri);
	return (adj);
}

int	ft_setenv(t_abs_struct *base, t_process *p)
{
	int			ret;
	char		**key_value;
	char		*tri;

	ret = 0;
	key_value = ft_split(p->argv[1], '=');
	if (key_value)
	{
		if (ft_search_env(base->env, key_value[0]))
			ft_unset(base, p);
		tri = ft_prepare_export(key_value[0], key_value[1]);
		ret = ft_add_line(&base->env, &base->lines_envp, tri);
		if (!tri || !(ret))
			ft_putstr("\e[0mNo se añadió el argumento\n");
		ft_array_release(key_value);
		if (tri)
			free(tri);
		return (ret);
	}
	ft_putstr("\e[0mError en los argumentos\n");
	base->error = 0;
	return (0);
}
