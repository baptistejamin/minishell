/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/20 14:15:23 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>

# define UNUSED(x) (void)(x)

typedef int	(*t_func)(void *sh, char **cmds);

typedef struct stat	t_stat;

typedef struct			s_builtin
{
	char				*name;
	t_func				func;
}						t_builtin;

typedef struct			s_sh
{
	char				**env;
	int					last_res;
	t_builtin			builtins[10];
}						t_sh;

char					*minishell_get_env(t_sh *sh, char *var);
char					**minishell_copy_env(char **env);
int						minishell_count_env(char **env);
int						minishell_launch_cmd(t_sh *sh, char *cmd, char **args);
void					minishell_init_builtins(t_sh *sh);
int						minishell_builtins_exit(void *sh_, char **cmds);
int						minishell_builtins_pwd(void *sh_, char **cmds);
int						minishell_builtins_cd(void *sh_, char **cmds);
int						minishell_builtins_env(void *sh_, char **cmds);
int						minishell_builtins_setenv(void *sh_, char **cmds);
int						minishell_builtins_unsetenv(void *sh_, char **cmds);
int						minishell_is_builtin(t_sh *sh, char **cmds);
int						minishell_boot_builtin(t_sh *sh, char **cmds);
void					minishell_errors_is_directory(char *cmd);
void					minishell_errors_not_found(char *cmd);
void					minishell_errors_no_file_directory(char *cmd);

#endif
