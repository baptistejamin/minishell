/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

static char **minishell_builtins_env_fresh_env(t_generic_options *options,
												char **cmds)
{
	int i;
	char **new_env;

	i = options->start;
	while(cmds[i])
		i++;
	new_env = malloc(sizeof(char **) * (i - options->start));
	new_env[i] = NULL;
	return (new_env);
}

/*static 	int minishell_builtins_env_set_vars(t_generic_options *options, char **env, char **cmds)
{
	int i;
	i = options->start;
	while(cmds[i])
	{
		if (ft_strchr(cmds[i], '='))
		{
			minishell_builtins_setenv_set(env, "SHLVL", ft_strdup("value"));
		}
		i++;
	}
	return (1);
}*/

int	minishell_builtins_env(void *sh_, char **cmds)
{
	t_sh				*sh;
	int					i;
	t_generic_options	options;
	char				**new_env;

	sh = (t_sh *)sh_;
	options = minishell_builtins_options_parser(cmds, "i");

	if (!ft_is_in(options.options, 'i'))
		new_env = minishell_copy_env(sh->env);
	else
		new_env = minishell_builtins_env_fresh_env(&options, cmds);
	i = 0;
	//minishell_builtins_env_set_vars(&options, new_env, cmds);
	while (new_env[i])
	{
		ft_putendl(new_env[i]);
		i++;
	}
	return (0);
}
