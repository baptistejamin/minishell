/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_helpers_cd.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:13:52 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/12 21:20:26 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		minishell_builtins_cd_error(int type, char *path)
{
	ft_putstr_fd("cd: ", 2);
	if (type == 0)
		ft_putstr_fd("An error occured\n", 2);
	else if (type == 1)
		ft_putstr_fd("too many arguments\n", 2);
	else if (type == 2)
		ft_putstr_fd("string not in pwd\n", 2);
	else if (type == 3)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (type == 4)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (type == 5)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	return (1);
}

char	*minishell_builtins_cd_assert_home(t_sh *sh)
{
	int		fd;
	char	*logname;
	char	*line;

	logname = minishell_get_env(sh, "LOGNAME");
	if (*minishell_get_env(sh, "HOME") == '\0')
	{
		fd = open("/etc/passwd", O_RDONLY);
		if (fd < 0 || !*logname)
			return (NULL);
		while (get_next_line(fd, &line))
		{
			if (ft_strncmp(logname, line, ft_strlen(logname)) == 0)
				return (ft_strrchr(line, ':') + 1);
		}
		close(fd);
		return (NULL);
	}
	return (minishell_get_env(sh, "HOME"));
}

char	*minishell_builtins_cd_assert_multiple_args(t_sh *sh, char **cmds)
{
	char	cdpath[PATH_MAX];
	char	directory[PATH_MAX];

	UNUSED(sh);
	if (cmds[3])
	{
		minishell_builtins_cd_error(1, "");
		return (NULL);
	}
	getcwd(cdpath, PATH_MAX);
	if (cmds[3] && !ft_strstr(cdpath, cmds[1]))
		minishell_builtins_cd_error(2, "");
	else
	{
		directory[0] = 0;
		ft_strncat(directory, cdpath, ft_strlen(cdpath) -
			ft_strlen(ft_strstr(cdpath, cmds[1])) - 1);
		ft_strcat(directory, "/");
		ft_strcat(directory, cmds[2]);
		ft_strcat(directory, ft_strstr(cdpath, cmds[1]) + ft_strlen(cmds[1]));
		return (ft_strdup(directory));
	}
	return (NULL);
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

int		minishell_builtins_cd_change_directory(t_sh *sh, char *curpath,
												int is_physical)
{
	t_stat		stat_;
	char		old_path[PATH_MAX];
	char		new_path[PATH_MAX];

	getcwd(old_path, 256);
	if (stat(curpath, &stat_) == -1)
		return (minishell_builtins_cd_error(3, curpath));
	if (!S_ISDIR(stat_.st_mode))
		return (minishell_builtins_cd_error(4, curpath));
	if (chdir(curpath) != 0)
		return (minishell_builtins_cd_error(5, curpath));
	getcwd(new_path, 256);
	if (is_physical)
		minishell_builtins_cd_update_path(sh, ft_strdup(old_path),
		curpath);
	else
		minishell_builtins_cd_update_path(sh, ft_strdup(old_path),
		ft_strdup(new_path));
	return (0);
}
