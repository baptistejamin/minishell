/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		minishell(t_sh *sh)
{
	char	**cmds;
	char	*cmd;
	int		res;

	res = 0;
	ft_putstr("$>");
	while (get_next_line(0, &cmd))
	{
		sh->last_res = res;
		cmd = ft_strfjoin(cmd, " ");
		cmds = ft_str_to_tab(cmd);
		res = minishell_boot(sh, sh->env_list, cmds);
		if (cmd)
			free(cmd);
		if (cmds)
			ft_free_tab(cmds);
		cmds = NULL;
		ft_putstr("$>");
	}
	if (sh->env_list)
	{
		ft_lstdel(&sh->env_list, &minishell_builtins_unsetenv_free);
		free(sh->env_list);
	}
	return (res);
}

int				main(int argc, char **argv, char **environ)
{
	t_sh	sh;
	char	*nb;

	UNUSED(argv);
	if (argc > 1)
	{
		ft_putendl_fd("minishell cannot execute commands", 2);
		return (0);
	}
	minishell_init_builtins(&sh);
	sh.env_list = NULL;
	minishell_env_to_list(&sh.env_list, environ);
	if (minishell_env_get(sh.env_list, "SHLVL"))
		nb = ft_itoa(ft_atoi(minishell_env_get(sh.env_list, "SHLVL")) + 1);
	else
		nb = ft_itoa(1);
	minishell_builtins_setenv_set(&sh.env_list, "SHLVL", nb);
	if (nb)
		free(nb);
	minishell_signals();
	return (minishell(&sh));
}
