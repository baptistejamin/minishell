/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_setenv.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	minishell_builtins_setenv_error_missing(void)
{
	ft_putendl_fd("setenv: You must provide a variable", 2);
	return (2);
}

static int	minishell_builtins_setenv_error_two_many(void)
{
	ft_putendl_fd("setenv: Two many arguments", 2);
	return (2);
}

void		minishell_builtins_setenv_add(t_list **list, char *var,
				char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->var = ft_strdup(var);
	env->value = ft_strdup(value);
	ft_lstadd(list, ft_lstnew(env, sizeof(t_env)));
}

int			minishell_builtins_setenv_set(t_list **list, char *var,
				char *value)
{
	t_list	*cur;
	t_env	*env;

	cur = *list;
	while (cur)
	{
		env = cur->content;
		if (ft_strcmp(env->var, var) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return (0);
		}
		cur = cur->next;
	}
	minishell_builtins_setenv_add(list, var, value);
	return (0);
}

int			minishell_builtins_setenv(void *sh_, t_list *environ, char **cmds)
{
	t_sh	*sh;
	int		i;

	UNUSED(cmds);
	sh = (t_sh *)sh_;
	i = 0;
	if (!cmds[1] || (cmds[1] && !cmds[2]))
		return (minishell_builtins_setenv_error_missing());
	if (cmds[2] && cmds[3])
		return (minishell_builtins_setenv_error_two_many());
	minishell_builtins_setenv_set(&environ, cmds[1], cmds[2]);
	return (0);
}
