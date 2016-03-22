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

int		minishell_builtins_cd_error_no_file_directory(char *path, int is_file)
{
	if (!is_file)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	return (2);
}

int		minishell_builtins_cd_error_permission(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (2);
}

void	minishell_builtins_cd_update_path(t_sh *sh, char *old_path, char *path)
{
	char	*cmds[4];

	cmds[0] = ft_strdup("setenv");
	cmds[1] = ft_strdup("OLDPWD");
	cmds[2] = old_path;
	cmds[3] = NULL;
	minishell_builtins_setenv(sh, cmds);
	cmds[0] = ft_strdup("setenv");
	cmds[1] = ft_strdup("PWD");
	cmds[2] = path;
	minishell_builtins_setenv(sh, cmds);
}

char	*minishell_builtins_cd_manage_home(t_sh *sh, char *path, char **cmds)
{
	if ((cmds[1] && ft_strcmp(cmds[1], "~") == 0) ||
		(cmds[1] && cmds[1][0] == '~' && ft_strchr(cmds[1], '/')))
	{
		if (ft_strchr(cmds[1], '/'))
			return (ft_strfjoin(ft_strjoin(minishell_get_env(sh, "HOME"), "/"),
				ft_strchr(cmds[1], '/')));
		else
			return (ft_strjoin(minishell_get_env(sh, "HOME"), "/"));
	}
	return (path);
}

int		minishell_builtins_cd(void *sh_, char **cmds)
{
	t_sh		*sh;
	t_stat		stat_;
	char		*path;
	char		old_path[257];
	char		new_path[257];

	sh = (t_sh *)sh_;
	if (cmds[1] && ft_strcmp(cmds[1], "-") == 0)
		cmds[1] = ft_strdup(minishell_get_env(sh, "OLDPWD"));
	path = cmds[1];
	path = minishell_builtins_cd_manage_home(sh, path, cmds);
	if (!path)
		path = ".";
	if (lstat(path, &stat_) == -1)
		return (minishell_builtins_cd_error_no_file_directory(path, 0));
	if (!S_ISDIR(stat_.st_mode))
		return (minishell_builtins_cd_error_no_file_directory(path, 1));
	getcwd(old_path, 256);
	if (chdir(path) != 0)
		return (minishell_builtins_cd_error_permission(path));
	getcwd(new_path, 256);
	minishell_builtins_cd_update_path(sh, ft_strdup(old_path),
		ft_strdup(new_path));
	return (0);
}
