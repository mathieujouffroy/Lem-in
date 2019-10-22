/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:28:54 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/22 13:52:36 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				addhash_links(t_links **list, t_links *l1, t_links *l2,
					unsigned long *h)
{
	t_links			*tmp;
	int				state;

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

int					get_link(t_lemin *lemin, t_links **tmp, char *line)
{
	t_links			*l1;
	t_links			*l2;
	unsigned long	h[2];
	char			**rooms;

	rooms = ft_strsplit(line, '-');
	h[0] = hashing((unsigned char*)rooms[0]);
	h[1] = hashing((unsigned char*)rooms[1]);
	if (h[0] == lemin->hashstart || h[1] == lemin->hashstart)
		lemin->state |= S_START;
	if (h[0] == lemin->hashend || h[1] == lemin->hashend)
		lemin->state |= S_END;
	if (!(are_hash_valid(*tmp, h)))
		return (FAILURE);
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

int					links_formatting(t_lemin *lemin, char *line)
{
	if (ft_strchr(line, '-') && (lemin->state & S_ROOMS)
	&& !ft_strchr(line, ' '))
		return (1);
	return (0);
}

int					parse_links(t_lemin *lemin, char *line)
{
	if (!(lemin->start && lemin->end))
		return (exit_with_message_links(line));
	if (rooms_errors(lemin) && !(lemin->state & S_LINKS))
		return (exit_with_message_links(line));
	if (!get_link(lemin, &lemin->list, line))
		return (exit_with_message_links(line));
	return (success_exit(line));
}
