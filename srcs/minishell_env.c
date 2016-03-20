/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char  **minishell_copy_env(char **env)
{
  int   i;
  char  **new;

  i = 0;
  new = NULL;
  while (env[i])
    i++;
  new = malloc(sizeof(char **) * (i + 1));
  i = 0;
  while (env[i])
  {
    new[i] = ft_strdup(env[i]);
    i++;
  }
  new[i] = NULL;
  return (new);
}

char	*minishell_get_env(t_sh *sh, char *var)
{
	int	i;

	i = 0;
	while (sh->env[i])
	{
		if (ft_strncmp(sh->env[i], var, ft_strlen(var)) == 0)
			return (ft_strchr(sh->env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
