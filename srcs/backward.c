/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backward.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:17:55 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/21 20:20:24 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					check_back_path(t_lemin *lemin, t_graph *room)
{
	t_links			*list;
	int				iroom;
	int				iadjacent;
	int				id;

	id = 0;
	list = room->links;
	iroom = room->index;
	while (list)
	{
		iadjacent = list->room->index;
		if ((list->room->hash != lemin->hashstart)
		&& (lemin->matrix[iadjacent][iroom] == 1)
		&& (lemin->matrix[iroom][iadjacent] == 0)
		&& (list->room->visited == false))
			id = list->room->index;
		list = list->next;
	}
	return (id);
}

void				go_backwards(t_links **queue, t_links *list, t_graph *room,
					int back)
{
	int				iadjactent;

	while (list)
	{
		iadjactent = list->room->index;
		if (list->room->index == back)
		{
			update_info_enqueue(queue, list, room);
			list->room->back = false;
		}
		list = list->next;
	}
}
