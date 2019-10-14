/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:28:54 by yabecret          #+#    #+#             */
/*   Updated: 2019/09/26 12:04:07 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void 	addhash_links(t_links **list, t_links *l1, t_links *l2, unsigned long *h)
{
	t_links	*tmp;
	int		state;

	tmp = *list;
	state = 0;
	while (tmp)
	{
		if ((state & S_R1) && (state & S_R2))
			break ;
		else if (!(state & S_R1) && (tmp->room->hash == h[0]))
		{
			l1->room = tmp->room;
			addlinks(&tmp->room->links, l2);
			state |= S_R1;
		}
		else if (!(state & S_R2) && (tmp->room->hash == h[1]))
		{
			l2->room = tmp->room;
			addlinks(&tmp->room->links, l1);
			state |= S_R2;
		}
		tmp = tmp->next;
	}
}

int 	get_link(t_lemin *lemin, t_links **tmp, char *line)
{
	t_links			*l1;
	t_links			*l2;
	unsigned long	h[2];
	char			**rooms;

	rooms = ft_strsplit(line, '-');
	h[0] = hashing((unsigned char*)rooms[0]);
	h[1] = hashing((unsigned char*)rooms[1]);
	if (!(are_hash_valid(*tmp, h)))
	{	
		ft_printf("1 :%s\n", rooms[0]);
		ft_printf("2 :%s\n", rooms[1]);
		return (FAILURE);
	}
	l1 = memalloc_links();
	l2 = memalloc_links();
	addhash_links(tmp, l1, l2, h);
	(lemin->state & S_LINKS) ? 0 : (lemin->state |= S_LINKS);
	free(rooms[0]);
	free(rooms[1]);
	free(rooms);
	add_line_to_str(lemin, line);
	return (SUCCESS);
}
