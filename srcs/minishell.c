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

void	launch_cmd(char *cmd)
{
	cmds = ft_str_to_tab(cmd);
}

void	parse_cmd(t_sh *sh, char *cmd)
{
	char	**path;
	char	**cmds;
	char	**tmp;
	int		i;

	path = ft_strsplit(minishell_get_env(sh, "PATH"), ':');
	i = 0;
	cmd = ft_strfjoin(cmd, " ");
	cmds = ft_str_to_tab(cmd);
	while (path && path[i])
	{
		tmp = ft_strfjoin(ft_strjoin(path[i], "/"), cmds[0]);
		if (access(tmp, X_OK) == 0)
		{
			cmds[0] = tmp;
			launch_cmd(cmd);
			return ;
		}
		if (tmp)
			free(tmp);
		tmp = NULL;
		free(path[i]);
		i++;
	}
	if (path)
		free(path);
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(mds[0], 2);
	ft_putstr_fd("\n", 2);
}

void	minishell(t_sh *sh)
{
	char	*cmd;

	while (1)
	{
		ft_putstr("$>");
		get_next_line(0, &cmd);
		parse_cmd(sh, cmd);
	}
}

int		main(int argc, char **argv, char **environ)
{
	t_sh	sh;
	sh.env = environ;
	sh.argc = argc;
	sh.argv = argv;
	minishell(&sh);
	return (0);
}
