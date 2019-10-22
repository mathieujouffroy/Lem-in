/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:05:52 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/23 00:33:29 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char *get_name(char *line)
{
	int i;
	long res;
	char **rooms;
	char *ret;

	if ((i = ft_cntchr(line, ' ')) != 2)
		return (NULL);
	rooms = ft_strsplit(line, ' ');
	i = 0;
	if (!rooms[0] || !rooms[1] || !rooms[2])
	{
		while (rooms[i])
		{
			free(rooms[i]);
			i++;
		}
		free(rooms);
		return (NULL);
	}
	while (i < 2)
	{
		res = ft_atoll(rooms[i + 1]);
		if (res > INT_MAX || res < INT_MIN)
		{
			ft_strdel(&rooms[1]);
			ft_strdel(&rooms[2]);
			ft_strdel(&rooms[0]);
			free(rooms);
			return (NULL);
		}
		i++;
	}
	ft_strdel(&rooms[1]);
	ft_strdel(&rooms[2]);
	ret = rooms[0];
	free(rooms);
	return (ret);
}

void room_start_or_end(t_lemin *lemin, t_links *links)
{
	if (is_start(lemin))
	{
		lemin->start = links->room->name;
		lemin->hashstart = links->room->hash;
		lemin->head = links->room;
	}
	else if (is_end(lemin))
	{
		lemin->end = links->room->name;
		lemin->hashend = links->room->hash;
		lemin->sink = links->room;
	}
}

t_links *init_links(t_lemin *lemin, char *name, unsigned long hash)
{
	t_links *links;

	links = memalloc_links();
	links->room = memalloc_graph();
	links->room->name = name;
	links->room->hash = hash;
	links->room->visited = false;
	links->room->index = lemin->cnt++;
	return (links);
}

int get_room(t_lemin *lemin, t_links **tmp, char *line)
{
	t_links *links;
	char *name;
	char *linetmp;
	unsigned long hash;

	linetmp = ft_strdup(line);
	if ((name = get_name(linetmp)) == NULL)
	{
		free(linetmp);
		return (-1);
	}
	hash = hashing((unsigned char *)name);
	if (is_hash_existing(*tmp, hash))
	{
		free(linetmp);
		free(name);
		return (FAILURE);
	}
	links = init_links(lemin, name, hash);
	room_start_or_end(lemin, links);
	addlinks(tmp, links);
	add_line_to_str(lemin, line);
	free(linetmp);
	!(lemin->state & S_ROOMS) ? (lemin->state |= S_ROOMS) : 0;
	return (SUCCESS);
}

int parse_room(t_lemin *lemin, char *line)
{
	int ret;

	if (is_room(line))
	{
		ret = get_room(lemin, &lemin->list, line);
		if (ret == 0)
			return (exit_with_message_room_duplicate(line));
		else if (ret == -1)
			return (exit_with_message_coord_overflow(line));
		return (success_exit(line));
	}
	else
		return (exit_with_message_room(line));
}
