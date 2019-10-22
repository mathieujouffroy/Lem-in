/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:27:12 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/22 14:07:57 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					backtrack(t_lemin *lemin)
{
	unsigned long	tracker;
	t_links			*tmp;
	unsigned int	cnt;

	tracker = lemin->hashend;
	cnt = 0;
	while (1)
	{
		if (tracker == 0)
		{
			lemin->container->len = cnt - 1;
			lemin->container->color_id = lemin->c_id;
			if (lemin->c_id == 8)
				lemin->c_id = 1;
			lemin->c_id++;
			return (SUCCESS);
		}
		tmp = find_hash_node(lemin->list, tracker);
		addlinks(&lemin->container->path, tmp);
		tracker = lemin->container->path->room->pred;
		cnt++;
	}
	return (FAILURE);
}

void				resetvisited(t_lemin *lemin)
{
	t_links			*tmp;

	tmp = lemin->list;
	while (tmp)
	{
		tmp->room->visited = false;
		tmp = tmp->next;
	}
}

void				initialize_lemin_for_ek(t_lemin *lemin)
{
	lemin->matrix = memalloc_matrix(lemin->cnt);
	lemin->container = memalloc_allpaths();
	lemin->max_steps = INT_MAX;
}

int					ek(t_lemin *lemin)
{
	int				tmp;
	unsigned int	max;
	t_allpaths		*tmp1;

	tmp = 1;
	initialize_lemin_for_ek(lemin);
	tmp1 = lemin->container;
	while (bfs(lemin) != 0 && tmp && (lemin->state & S_END))
	{
		max = 0;
		backtrack(lemin);
		tmp = nbr_steps(lemin, tmp1, max);
		if (tmp == -1)
			return (FAILURE);
		tmp ? lemin->max_steps = tmp : lemin->max_steps;
		resetvisited(lemin);
		if (!updatematrix(lemin))
			break ;
	}
	lemin->container = tmp1;
	if (lemin->container->path == NULL)
		return (FAILURE);
	delete_path_too_big(lemin, lemin->container);
	delete_extra_node(lemin, lemin->container);
	return (SUCCESS);
}
