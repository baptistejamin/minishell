/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	file_cmd(t_sh *sh, t_list *environ, char **cmds)
{
	struct stat stat_;

	if (lstat(cmds[0], &stat_) == -1)
	{
		minishell_errors_no_file_directory(cmds[0]);
		return (-1);
	}
	if (S_ISDIR(stat_.st_mode))
	{
		minishell_errors_is_directory(cmds[0]);
		return (-1);
	}
	if (access(cmds[0], X_OK) == 0)
		return (minishell_launch_cmd(sh, environ, cmds[0], cmds));
	minishell_errors_no_file_directory(cmds[0]);
	return (-1);
}

int			minishell_launch_cmd(t_sh *sh, t_list *environ, char *cmd,
					char **args)
{
	pid_t	pid;
	int		res;

	UNUSED(sh);
	res = -1;
	if ((pid = fork()) != 0)
		waitpid(pid, &res, 0);
	else
		execve(cmd, args, minishell_env_from_list(environ));
	return (res);
}

int			minishell_boot_cmd(t_sh *sh, t_list *environ, char **cmds)
{
	char	**path;
	char	*tmp;
	int		i;

	path = ft_strsplit(minishell_env_get(sh->env_list, "PATH"), ':');
	i = 0;
	if (ft_strchr(cmds[0], '/') != NULL)
		return (file_cmd(sh, environ, cmds));
	while (path && path[i])
	{
		tmp = ft_strfjoin(ft_strjoin(path[i], "/"), cmds[0]);
		if (access(tmp, X_OK) == 0)
		{
			ft_free_tab(path);
			return (minishell_launch_cmd(sh, environ, tmp, cmds));
		}
		free(tmp);
		tmp = NULL;
		i++;
	}
	minishell_errors_not_found(cmds[0]);
	if (path)
		ft_free_tab(path);
	return (-1);
}

int			minishell_boot(t_sh *sh, t_list *environ, char **cmds)
{
	if (cmds[0] && minishell_is_builtin(sh, cmds))
		return (minishell_boot_builtin(sh, environ, cmds));
	else if (cmds[0])
		return (minishell_boot_cmd(sh, environ, cmds));
	return (-1);
}
