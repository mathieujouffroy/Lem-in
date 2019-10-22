/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:42:34 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/21 20:29:57 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** hash * 33 + c
*/

unsigned long		hashing(unsigned char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

int					is_hash_existing(t_links *tmp, unsigned long hash)
{
	while (tmp)
	{
		if (tmp->room->hash == hash)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int					are_hash_valid(t_links *tmp, unsigned long *h)
{
	int				state;

	state = 0;
	while (tmp)
	{
		if (!(state & S_R1) && (tmp->room->hash == h[0]))
			state |= S_R1;
		else if (!(state & S_R2) && (tmp->room->hash == h[1]))
			state |= S_R2;
		tmp = tmp->next;
	}
	return (((state & S_R1) && (state & S_R2)) ? SUCCESS : FAILURE);
}

t_links				*find_hash_node(t_links *list, unsigned long hash)
{
	t_links			*new;
	t_links			*tmp;

	new = memalloc_links();
	tmp = list;
	while (tmp)
	{
		if (tmp->room && tmp->room->hash == hash)
		{
			new->room = tmp->room;
			new->next = NULL;
			return (new);
		}
		tmp = tmp->next;
	}
	return (new);
}
