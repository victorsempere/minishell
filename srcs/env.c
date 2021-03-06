/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:16 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 17:09:20 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_copy_env(t_abs_struct *base, char **envp)
{
	if (!base)
		return (0);
	base->env = ft_array_dup(envp);
	base->lines_envp = ft_array_len(envp);
	return (1);
}

int	ft_env(t_abs_struct *base, t_process *p)
{
	char	**envp;
	char	*arg;

	arg = get_first_non_empty_arg(p->argv + 1);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": No se encontró el fichero o directorio\n",
			STDERR_FILENO);
		p->status = 127;
		base->last_status = p->status;
		return (0);
	}
	envp = base->env;
	while (envp && *envp)
	{
		ft_putstr(*envp);
		ft_putstr("\n");
		envp++;
	}
	return (1);
}

static void	handle_unset_invalid_argument(t_abs_struct *base, t_process *p,
				char *argv)
{
	ft_putstr_fd("unset: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd("': Invalid identifier\n", STDERR_FILENO);
	p->status = 1;
	base->last_status = p->status;
}

void	ft_unset(t_abs_struct *base, t_process *p)
{
	char	**argv;
	int		keypos;

	if (!p || ft_array_len(p->argv) <= 1)
	{
		base->last_status = 0;
		return ;
	}
	argv = p->argv + 1;
	while (argv && *argv)
	{
		argv = get_first_non_empty_arg_pos(argv);
		if (!argv)
			break ;
		if (!is_env_valid_argument(*argv))
			handle_unset_invalid_argument(base, p, *argv);
		else
		{
			keypos = ft_search_env(base->env, *argv);
			if (keypos >= 0
				&& !ft_array_delete_pos(&base->env, &base->lines_envp, keypos))
				ft_exit_minishell(1);
		}
		argv++;
	}
}

void	ft_delete_existing_key(t_abs_struct *base, char *key)
{
	int	key_pos;

	key_pos = ft_search_env(base->env, key);
	if (key_pos >= 0
		&& !ft_array_delete_pos(&base->env, &base->lines_envp, key_pos))
		ft_exit_minishell(1);
}
