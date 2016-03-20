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

int		minishell_builtins_setenv_error_missing(void)
{
	ft_putendl_fd("setenv: You must provide a variable", 2);
	return (2);
}

int		minishell_builtins_setenv_error_two_many(void)
{
	ft_putendl_fd("setenv: Two many arguments", 2);
	return (2);
}

void	minishell_builtins_addenv(t_sh *sh, char **cmds)
{
	int		i;
	char	**new;

	i = 0;
	new = NULL;
	while (sh->env[i])
		i++;
	new = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while (sh->env[i])
	{
		new[i] = ft_strdup(sh->env[i]);
		i++;
	}
	new[i] = ft_strfjoin(ft_strjoin(cmds[1], "="), cmds[2]);
	new[i + 1] = NULL;
	ft_free_tab(sh->env);
	sh->env = new;
}

int		minishell_builtins_setenv(void *sh_, char **cmds)
{
	t_sh	*sh;
	int		i;

	UNUSED(cmds);
	sh = (t_sh *)sh_;
	i = 0;
	if (!cmds[1])
		return (minishell_builtins_setenv_error_missing());
	if (cmds[2] && cmds[3])
		return (minishell_builtins_setenv_error_two_many());
	while (sh->env[i])
	{
		if ((ft_strncmp(sh->env[i], cmds[1], ft_strlen(cmds[1])) == 0) &&
			cmds[2])
		{
			free(sh->env[i]);
			sh->env[i] = ft_strfjoin(ft_strjoin(cmds[1], "="), cmds[2]);
			return (0);
		}
		i++;
	}
	if (cmds[2])
		minishell_builtins_addenv(sh_, cmds);
	return (0);
}
