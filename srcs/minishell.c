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

int		file_cmd(t_sh *sh, t_list *environ, char **cmds)
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

int		minishell_launch_cmd(t_sh *sh, t_list *environ, char *cmd, char **args)
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

int		minishell_boot_cmd(t_sh *sh, t_list *environ, char **cmds)
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
			return (minishell_launch_cmd(sh, environ, tmp, cmds));
		free(tmp);
		tmp = NULL;
		i++;
	}
	minishell_errors_not_found(cmds[0]);
	if (path)
		ft_free_tab(path);
	return (-1);
}

int		minishell_boot(t_sh *sh, t_list *environ, char **cmds)
{
	if (cmds[0] && minishell_is_builtin(sh, cmds))
		return (minishell_boot_builtin(sh, cmds));
	else if (cmds[0])
		return (minishell_boot_cmd(sh, environ, cmds));
	return (-1);
}

int		minishell(t_sh *sh)
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
		ft_lstdel(&sh->env_list, &minishell_builtins_unsetenv_free);
	return (res);
}

int		main(int argc, char **argv, char **environ)
{
	t_sh	sh;
	char 	*nb;

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
	{
		nb = ft_itoa(ft_atoi(minishell_env_get(sh.env_list, "SHLVL")) + 1);
		minishell_builtins_setenv_set(&sh.env_list, "SHLVL", nb);
	}
	else
	{
		nb = ft_itoa(1);
		minishell_builtins_setenv_set(&sh.env_list, "SHLVL", nb);
	}
	if (nb)
		free(nb);
	minishell_signals();
	return (minishell(&sh));
}
