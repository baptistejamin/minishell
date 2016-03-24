/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_unsetenv.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <ctype.h>

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 8
#endif

void hexdump(void *mem, unsigned int len)
{
        unsigned int i, j;

        for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++)
        {
                /* print offset */
                if(i % HEXDUMP_COLS == 0)
                {
                        printf("0x%06x: ", i);
                }

                /* print hex data */
                if(i < len)
                {
                        printf("%02x ", 0xFF & ((char*)mem)[i]);
                }
                else /* end of block, just aligning for ASCII dump */
                {
                        printf("   ");
                }

                /* print ASCII dump */
                if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
                {
                        for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
                        {
                                if(j >= len) /* end of block, not really printing */
                                {
                                        putchar(' ');
                                }
                                else if(isprint(((char*)mem)[j])) /* printable char */
                                {
                                        putchar(0xFF & ((char*)mem)[j]);
                                }
                                else /* other char */
                                {
                                        putchar('.');
                                }
                        }
                        putchar('\n');
                }
        }
}

int		minishell_builtins_unsetenv_error_missing(void)
{
	ft_putendl_fd("unsetenv: You must provide a variable", 2);
	return (2);
}

int		minishell_builtins_unsetenv_error_two_many(void)
{
	ft_putendl_fd("unsetenv: Two many arguments", 2);
	return (2);
}

void	minishell_builtins_unsetenv_free(void *content, size_t size)
{
	t_env		*env;

	UNUSED(size);
	env = content;

	if (!content)
		return ;
	if (env->var)
		free(env->var);
	if (env->value)
		free(env->value);
	free(env);
}

int		minishell_builtins_unsetenv(void *sh_, char **cmds)
{
	t_sh		*sh;
	t_list	*cur;
	t_env		*env;
	int			i;

	sh = (t_sh *)sh_;
	if (!cmds[1])
		return (minishell_builtins_unsetenv_error_missing());
	if (cmds[2])
		return (minishell_builtins_unsetenv_error_two_many());
	i = 0;
	cur = sh->env_list;
	while (cur)
	{
		env = cur->content;
		cur = cur->next;
		if (ft_strcmp(cmds[1], env->var) == 0)
		{
			ft_lstdel_at(&sh->env_list, i, &minishell_builtins_unsetenv_free);
			return (0);
		}
		i++;
	}
	return (0);
}
