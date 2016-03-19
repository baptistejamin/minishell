/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:07:27 by bjamin            #+#    #+#             */
/*   Updated: 2015/12/04 11:06:05 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			words++;
			s++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**word_tab;
	size_t	nb_words;
	size_t	index;
	char	*tmp;

	tmp = (char *)s;
	if (!tmp)
		return (NULL);
	index = 0;
	nb_words = ft_count_words(tmp, c);
	word_tab = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!word_tab)
		return (NULL);
	while (word_tab && index < nb_words)
	{
		while (*tmp && *tmp == c)
			tmp++;
		word_tab[index] = ft_strsub(tmp, 0, ft_wordlen(tmp, c));
		if (word_tab[index] == NULL)
			return (NULL);
		tmp += ft_wordlen(s, c);
		index++;
	}
	word_tab[index] = NULL;
	return (word_tab);
}
