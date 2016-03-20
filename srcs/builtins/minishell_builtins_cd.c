/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void   minishell_builtins_cd_error_no_file_directory(char *path)
{
  ft_putstr_fd("cd: ", 2);
  ft_putstr_fd(path, 2);
  ft_putstr_fd(": No such file or directory\n", 2);
}

void   minishell_builtins_cd_error_not_directory(char *path)
{
  ft_putstr_fd("cd: ", 2);
  ft_putstr_fd(path, 2);
  ft_putstr_fd(": Not a directory\n", 2);
}

void   minishell_builtins_cd_error_permission(char *path)
{
  ft_putstr_fd("cd: ", 2);
  ft_putstr_fd(path, 2);
  ft_putstr_fd(": Permission denied\n", 2);
}

int   minishell_builtins_cd(void *sh_, char **cmds)
{
  t_sh        *sh;
  struct stat stat_;
  char        *path;

  sh = (t_sh *)sh_;
  path = cmds[1] ? cmds[1] : minishell_get_env(sh, "HOME");
  if (!path)
    path = ".";
  if (lstat(path, &stat_) == -1)
  {
    minishell_builtins_cd_error_no_file_directory(path);
    return (2);
  }
  if (!S_ISDIR(stat_.st_mode))
  {
    minishell_builtins_cd_error_not_directory(path);
    return (2);
  }
  if (chdir(path) != 0)
  {
    minishell_builtins_cd_error_permission(path);
    return (2);
  }
  return (0);
}
