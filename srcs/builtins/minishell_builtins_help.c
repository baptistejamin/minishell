/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_help.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		minishell_builtins_help(void *sh_, char **cmds)
{
	UNUSED(sh_);
	UNUSED(cmds);
	ft_putendl("help:\n");
	ft_putendl("builtins:");
	ft_putendl("cd [path]");
	ft_putendl("exit [code]");
	ft_putendl("env [var]");
	ft_putendl("setenv [var] [value]");
	ft_putendl("unsetenv [var]");
	return (0);
}