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

int		file_cmd(t_sh *sh, char **cmds)
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
		return (minishell_launch_cmd(sh, cmds[0], cmds));
	minishell_errors_no_file_directory(cmds[0]);
	return (-1);
}

int		minishell_launch_cmd(t_sh *sh, char *cmd, char **args)
{
	pid_t	pid;
	int		res;

	res = -1;
	if ((pid = fork()) != 0)
		waitpid(pid, &res, 0);
	else
		execve(cmd, args, sh->env);
	return (res);
}

int		boot_cmd(t_sh *sh, char **cmds)
{
	char	**path;
	char	*tmp;
	int		i;

	path = ft_strsplit(minishell_get_env(sh, "PATH"), ':');
	i = 0;
	if (ft_strchr(cmds[0], '/') != NULL)
		return (file_cmd(sh, cmds));
	while (path && path[i])
	{
		tmp = ft_strfjoin(ft_strjoin(path[i], "/"), cmds[0]);
		if (access(tmp, X_OK) == 0)
			return (minishell_launch_cmd(sh, tmp, cmds));
		free(tmp);
		tmp = NULL;
		i++;
	}
	minishell_errors_not_found(cmds[0]);
	ft_free_tab(path);
	return (-1);
}

int		minishell(t_sh *sh)
{
	char	**cmds;
	char	*cmd;
	int		res;
	int		gnl;

	res = 0;
	gnl = 1;
	while (gnl)
	{
		ft_putstr("$>");
		gnl = get_next_line(0, &cmd);
		sh->last_res = res;
		cmd = ft_strfjoin(cmd, " ");
		cmds = ft_str_to_tab(cmd);
		if (cmds[0] && minishell_is_builtin(sh, cmds))
			res = minishell_boot_builtin(sh, cmds);
		else if (cmds[0] && ft_strcmp(cmd, " ") != 0)
			res = boot_cmd(sh, cmds);
		if (cmds)
			ft_free_tab(cmds);
		if (cmd)
			free(cmd);
		cmds = NULL;
	}
	if (sh->env)
		ft_free_tab(sh->env);
	return (res);
}

int		main(int argc, char **argv, char **environ)
{
	t_sh	sh;
	char	*cmds[4];

	UNUSED(argv);
	if (argc > 1)
	{
		ft_putendl_fd("minishell cannot execute commands", 2);
		return (0);
	}
	minishell_init_builtins(&sh);
	sh.env = minishell_copy_env(environ);
	cmds[0] = ft_strdup("setenv");
	cmds[1] = ft_strdup("SHLVL");
	cmds[3] = NULL;
	if (minishell_get_env(&sh, "SHLVL"))
		cmds[2] = ft_itoa(ft_atoi(minishell_get_env(&sh, "SHLVL")) + 1);
	else
		cmds[2] = ft_itoa(1);
	minishell_builtins_setenv(&sh, cmds);
	minishell_signals();
	return (minishell(&sh));
}
