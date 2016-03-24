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


static 	int minishell_builtins_env_set_vars(t_generic_options *options, t_list **list, char **cmds)
{
	int i;
	char *var;
	char *value;
	i = options->start;
	while(cmds[i])
	{
		if (ft_strchr(cmds[i], '='))
		{
			var = ft_strnew(ft_strlen(cmds[i]) -
			ft_strlen(ft_strchr(cmds[i], '=') + 1));
			ft_strncpy(var, cmds[i], ft_strlen(cmds[i]) -
			ft_strlen(ft_strchr(cmds[i], '=')));
			value = ft_strdup(ft_strchr(cmds[i], '=') + 1);
			minishell_builtins_setenv_set(list, var, value);
			free(var);
			free(value);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	minishell_builtins_env(void *sh_, char **cmds)
{
	t_sh							*sh;
	t_generic_options	options;
	t_list						*new_env;
	int								cmd_index;

	sh = (t_sh *)sh_;
	options = minishell_builtins_options_parser(cmds, "i");

	new_env = NULL;
	if (!ft_is_in(options.options, 'i'))
		ft_lstcpy(&new_env, sh->env_list);
	cmd_index = minishell_builtins_env_set_vars(&options, &new_env, cmds);
	if (!cmds[cmd_index])
		minishell_env_show(new_env);
	else
	{
		minishell_boot(sh, new_env, &cmds[cmd_index]);
	}

	return (0);
}
