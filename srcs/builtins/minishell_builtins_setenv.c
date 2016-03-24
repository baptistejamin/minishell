/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_setenv.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		minishell_builtins_setenv_error_missing(void)
{
	ft_putendl_fd("setenv: You must provide a variable", 2);
	return (2);
}

static int		minishell_builtins_setenv_error_two_many(void)
{
	ft_putendl_fd("setenv: Two many arguments", 2);
	return (2);
}

static void	minishell_builtins_setenv_add(char **env, char *var, char *value)
{
	int		i;
	char	**new;

	i = 0;
	new = NULL;
	while (env[i])
		i++;
	new = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = ft_strfjoin(ft_strjoin(var, "="), value);
	new[i + 1] = NULL;
	ft_free_tab(env);
	env = new;
}

int		minishell_builtins_setenv_set(char **env, char *var, char *value)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(var, env[i], ft_strlen(var)) == 0) &&
			value)
		{
			free(env[i]);
			env[i] = ft_strfjoin(ft_strjoin(var, "="), value);
			return (0);
		}
		i++;
	}
	if (value)
		minishell_builtins_setenv_add(env, var, value);
	return (0);
}


int		minishell_builtins_setenv(void *sh_, char **cmds)
{
	t_sh	*sh;
	int		i;

	UNUSED(cmds);
	sh = (t_sh *)sh_;
	i = 0;
	if (!cmds[1] || (cmds[1] && !cmds[2]))
		return (minishell_builtins_setenv_error_missing());
	if (cmds[2] && cmds[3])
		return (minishell_builtins_setenv_error_two_many());
	minishell_builtins_setenv_set(sh->env, cmds[1], cmds[2]);
	return (0);
}
