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
# include <fcntl.h>

# define UNUSED(x) (void)(x)
# define PATH_MAX 4096

typedef int	(*t_func)(void *sh, t_list *environ, char **cmds);

typedef struct stat	t_stat;

typedef struct		s_builtin
{
	char			*name;
	t_func			func;
}					t_builtin;

typedef struct		s_generic_options
{
	char			options[256];
	int				start;
	int				error;
	int				error_char;
	int				options_counter;
}					t_generic_options;

typedef struct		s_env
{
	char			*var;
	char			*value;
}					t_env;

typedef struct		s_sh
{
	char			**env;
	t_list			*env_list;
	int				last_res;
	t_builtin		builtins[10];
}					t_sh;

void				minishell_signals();
void				minishell_env_to_list(t_list **list, char **environ);
void				minishell_env_show(t_list *list);
char				**minishell_env_from_list(t_list *list);
char				*minishell_env_get(t_list *list, char *var);
char				**minishell_copy_env(char **env);
int					minishell_count_env(char **env);
int					minishell_launch_cmd(t_sh *sh, t_list *environ,
									char *cmd, char **args);
int					minishell_boot(t_sh *sh, t_list *environ, char **cmds);
void				minishell_init_builtins(t_sh *sh);
int					minishell_builtins_exit(void *sh_, t_list *environ,
									char **cmds);
int					minishell_builtins_help(void *sh_, t_list *environ,
									char **cmds);
int					minishell_builtins_pwd(void *sh_, t_list *environ,
									char **cmds);
int					minishell_builtins_cd(void *sh, t_list *environ,
									char **cmds);
int					minishell_builtins_env(void *sh_, t_list *environ,
									char **cmds);
int					minishell_builtins_setenv_set(t_list **list,
									char *var, char *value);
void				minishell_builtins_setenv_add(t_list **list, char *var,
									char *value);
int					minishell_builtins_setenv(void *sh_,
									t_list *environ, char **cmds);
int					minishell_builtins_unsetenv(void *sh_, t_list *environ,
								char **cmds);
void				minishell_builtins_unsetenv_free(void *content,
								size_t content_size);
int					minishell_is_builtin(t_sh *sh, char **cmds);
int					minishell_boot_builtin(t_sh *sh, t_list *environ,
								char **cmds);
int					minishell_boot_cmd(t_sh *sh, t_list *environ,
								char **cmds);
void				minishell_errors_is_directory(char *cmd);
void				minishell_errors_not_found(char *cmd);
void				minishell_errors_no_file_directory(char *cmd);
t_generic_options	minishell_builtins_options_parser(char **cmds,
							char *managed_options);
int					minishell_builtins_cd_change_directory(t_sh *sh,
							t_list *environ, char *curpath, int is_physical);
void				minishell_builtins_cd_update_path(t_sh *sh,
							t_list *environ, char *old_path, char *path);
char				*minishell_builtins_cd_assert_multiple_args(t_sh *sh,
							char **cmds);
char				*minishell_builtins_cd_assert_home(t_sh *sh,
							t_list *environ);
int					minishell_builtins_cd_error(int type, char *path);

#endif
