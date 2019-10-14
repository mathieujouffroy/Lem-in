/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:23:30 by yabecret          #+#    #+#             */
/*   Updated: 2018/11/14 11:20:08 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_newlen(char *s, char c)
{
	size_t n;

	while (*s && *s == c)
		s++;
	n = (*s ? 1 : 0);
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1))
			n++;
		s++;
	}
	return (n);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	n;
	char	*tmp;
	char	**new;

	if (!s)
		return (NULL);
	n = ft_newlen((char*)s, c);
	if (!(new = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	tmp = (char*)s;
	while (*s)
	{
		if (*s == c)
		{
			if (tmp != s)
				*(new++) = ft_strsub(tmp, 0, s - tmp);
			tmp = (char*)s + 1;
		}
		s++;
	}
	if (tmp != s)
		*(new++) = ft_strsub(tmp, 0, s - tmp);
	*new = NULL;
	return (new - n);
}
