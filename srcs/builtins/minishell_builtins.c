/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell_init_builtin(t_builtin *buitin, char *name, t_func func)
{
	buitin->name = name;
	buitin->func = func;
}

void	minishell_init_builtins(t_sh *sh)
{
	minishell_init_builtin(&sh->builtins[0], "pwd", &minishell_builtins_pwd);
	minishell_init_builtin(&sh->builtins[1], "exit", &minishell_builtins_exit);
	minishell_init_builtin(&sh->builtins[2], "cd", &minishell_builtins_cd);
	minishell_init_builtin(&sh->builtins[3], "env", &minishell_builtins_env);
	minishell_init_builtin(&sh->builtins[4], "setenv",
		&minishell_builtins_setenv);
	minishell_init_builtin(&sh->builtins[5], "unsetenv",
		&minishell_builtins_unsetenv);
	minishell_init_builtin(&sh->builtins[7], "", &minishell_builtins_exit);
}

int		minishell_boot_builtin(t_sh *sh, char **cmds)
{
	int i;

	i = 0;
	while (sh->builtins[i].name[0] != '\0')
	{
		if (ft_strcmp(sh->builtins[i].name, cmds[0]) == 0)
			return (sh->builtins[i].func(sh, cmds));
		i++;
	}
	return (0);
}

int		minishell_is_builtin(t_sh *sh, char **cmds)
{
	int i;

	i = 0;
	while (sh->builtins[i].name[0] != '\0')
	{
		if (ft_strcmp(sh->builtins[i].name, cmds[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}
