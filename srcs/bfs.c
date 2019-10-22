/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:21:52 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/22 16:57:19 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				sink_in_queue(t_lemin *lemin, t_links *queue)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
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

t_links			*init_queue_bfs(t_lemin *lemin)
{
	t_links		*new;
	t_links		*queue;

	queue = NULL;
	new = memalloc_links();
	new->room = lemin->head;
	enqueue(&queue, new);
	queue->room->visited = true;
	return (queue);
}

int				bfs_exit_or_malloc_path(t_lemin *lemin, int sink)
{
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
	return (1);
}

int				bfs(t_lemin *lemin)
{
	t_links		*queue;
	t_links		*todelete;
	int			cnt;
	int			sink;

	sink = 0;
	cnt = 0;
	todelete = NULL;
	queue = init_queue_bfs(lemin);
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
	if (bfs_exit_or_malloc_path(lemin, sink) == 0)
		return (0);
	return (cnt);
}
