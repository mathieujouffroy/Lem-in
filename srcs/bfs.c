/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:21:52 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/21 19:20:47 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		sink_in_queue(t_lemin *lemin, t_links *queue)
{
	int i = 0;
	int j = 0;

	while (queue != NULL)
	{
		i++;
		if (queue->room->name != lemin->end)
			j++;
		queue = queue->next;
	}
	if (i == j)
		return (0);
	else
		return (1);
}


int			bfs(t_lemin *lemin)
{
	t_links 		*queue;
	t_links			*new;
	t_links 		*todelete;
	int				cnt;
	int				sink;

	sink = 0;
	cnt = 0;
	queue = NULL;
	todelete = NULL;
	new = memalloc_links();
	new->room = lemin->head;
	enqueue(&queue, new);
	queue->room->visited = true;
	while (queue != NULL)
	{
		enqueue_adjacent(lemin, &queue, queue->room);
		todelete = queue;
		sink += sink_in_queue(lemin, queue);
		queue = queue->next;
		if (queue)
			cnt++;
		free(todelete);
	}
	if (sink == 0)
	{
		lemin->state &= ~S_END;
		return (FAILURE);
	}
	if (lemin->container && lemin->container->len != 0)
	{
		lemin->container->next = memalloc_allpaths();
		lemin->container = lemin->container->next;
	}
	return (cnt);
}
