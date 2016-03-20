/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int   minishell_builtins_env(void *sh_, char **cmds)
{
  t_sh  *sh;
  int   i;

  UNUSED(cmds);
  sh = (t_sh *)sh_;
  i = 0;
  while (sh->env[i])
  {
    ft_putendl(sh->env[i]);
    i++;
  }
  return (0);
}
