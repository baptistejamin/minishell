/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/20 13:40:16 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

static int	cd_move_path(t_sh *sh, t_generic_options *options, char *curpath)
{
	if (ft_is_in(options->options, 'P') && !ft_is_in(options->options, 'L'))
	{
		if (*curpath == '/')
			curpath = ft_strfjoin(ft_strjoin(
				minishell_get_env(sh, "PWD"), "/"), curpath);
		return (minishell_builtins_cd_change_directory(sh, curpath, 1));
	}
	else
		return (minishell_builtins_cd_change_directory(sh, curpath, 0));
}

int			minishell_builtins_cd(void *sh_, char **cmds)
{
	t_generic_options	options;
	char				*directory;
	char				*curpath;
	t_sh				*sh;

	sh = (t_sh *)sh_;
	options = minishell_builtins_options_parser(cmds, "LP");
	directory = cmds[options.start];
	if (!directory || ft_strcmp(cmds[1], "~") == 0)
		directory = minishell_builtins_cd_assert_home(sh);
	if (!directory)
		return (minishell_builtins_cd_error(0, ""));
	if (ft_strcmp(cmds[1], "-") == 0)
		directory = minishell_get_env(sh, "OLDPWD");
	if (cmds[1] && cmds[2])
	{
		directory = minishell_builtins_cd_assert_multiple_args(sh, cmds);
		if (!directory)
			return (1);
	}
	curpath = directory;
	return (cd_move_path(sh, &options, curpath));
}
