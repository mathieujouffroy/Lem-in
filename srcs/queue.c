/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:06:18 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/22 16:35:35 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				enqueue(t_links **links, t_links *new)
{
	t_links			*tmp;

	tmp = *links;
	if (!new)
		return ;
	if (!tmp)
	{
		*links = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void				update_info_enqueue(t_links **queue, t_links *list,
					t_graph *room)
{
	char			*name;
	unsigned long	pred;
	t_links			*tmp;

	tmp = NULL;
	name = room->name;
	pred = room->hash;
	list->room->visited = true;
	list->room->pred = pred;
	list->room->parent = name;
	tmp = memalloc_links();
	tmp->room = list->room;
	enqueue(queue, tmp);
}

int					node_used_in_path(t_lemin *lemin, t_graph *adjacent)
{
	int				i;
	int				iadjacent;
	int				back;
	int				used;

	i = 0;
	back = 0;
	used = 0;
	iadjacent = adjacent->index;
	back = check_back_path(lemin, adjacent);
	while (i < lemin->cnt)
	{
		if (lemin->matrix[iadjacent][i] == 1)
			used = 1;
		i++;
	}
	if (used == 1 && back != 0)
		return (0);
	else if (used == 1 && back == 0)
		return (1);
	else if (used == 0)
		return (0);
	return (0);
}

void				enqueue_adjacent(t_lemin *lemin, t_links **queue,
					t_graph *room)
{
	t_links			*list;
	int				iroom;
	int				iadjacent;
	int				back;

	list = room->links;
	iroom = room->index;
	if ((room->back == true) && (back = check_back_path(lemin, room)))
		go_backwards(queue, list, room, back);
	else
	{
		while (list)
		{
			iadjacent = list->room->index;
			if (list->room->visited == false
			&& lemin->matrix[iroom][iadjacent] == 0
			&& (!node_used_in_path(lemin, list->room)))
			{
				update_info_enqueue(queue, list, room);
				list->room->back = true;
			}
			list = list->next;
		}
	}
}
