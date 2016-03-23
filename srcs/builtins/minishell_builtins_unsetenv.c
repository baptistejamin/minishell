/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_unsetenv.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		minishell_builtins_unsetenv_error_missing(void)
{
	ft_putendl_fd("unsetenv: You must provide a variable", 2);
	return (2);
}

int		minishell_builtins_unsetenv_error_two_many(void)
{
	ft_putendl_fd("unsetenv: Two many arguments", 2);
	return (2);
}

int		minishell_builtins_unsetenv(void *sh_, char **cmds)
{
	t_sh	*sh;
	char	**new;
	int		i;
	int		n;

	sh = (t_sh *)sh_;
	new = malloc(sizeof(char **) * (minishell_count_env(sh->env)));
	i = 0;
	n = -1;
	if (!cmds[1])
		return (minishell_builtins_unsetenv_error_missing());
	if (cmds[2])
		return (minishell_builtins_unsetenv_error_two_many());
	while (sh->env[i])
	{
		if ((ft_strncmp(cmds[1], sh->env[i], ft_strlen(cmds[1])) != 0))
		{
			new[++n] = ft_strdup(sh->env[i]);
		}
		i++;
	}
	new[n] = NULL;
	ft_free_tab(sh->env);
	sh->env = new;
	return (0);
}
