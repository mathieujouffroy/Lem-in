/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:27:12 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/21 19:21:24 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links		*find_hash_node(t_links *list, unsigned long hash)
{
	t_links			*new;
	t_links			*tmp;

	new = memalloc_links();
	tmp = list;
	//new = tmp;
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

int			backtrack(t_lemin *lemin)
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
			return (SUCCESS);
		}
		tmp = find_hash_node(lemin->list, tracker);
		addlinks(&lemin->container->path, tmp);
		tracker = lemin->container->path->room->pred;
		cnt++;
	}
	return (FAILURE);
}

void		resetvisited(t_lemin *lemin)
{
	t_links 		*tmp;

	tmp = lemin->list;
	while (tmp)
	{
		tmp->room->visited = false;
		tmp = tmp->next;
	}
}

void		delete_extra_node(t_lemin *lemin, t_allpaths *head)
{
	t_allpaths	*nodebeforedel;
	t_allpaths	*del;

	del = head;
	nodebeforedel =  head;
	while (del->next != NULL)
	{
		nodebeforedel = del;
		del = del->next;
	}
	if (del->len == 0)
	{
		nodebeforedel->next = NULL;
		lemin->nb_pathsbfs > 1 ? lemin->nb_pathsbfs-- : 0;
		freeallpaths(del);
	//	ft_memdel((void**)del);
	}
}

void		delete_node(t_lemin *lemin, t_allpaths *head)
{
	t_allpaths	*nodebeforedel;
	t_allpaths	*del;


	del = head;
	nodebeforedel =  head;
	while (del->next != NULL)
	{
		nodebeforedel = del;
		del = del->next;
	}
	if (del->len > lemin->max_steps)
	{
		nodebeforedel->next = NULL;
		freeallpaths(del);
	//	ft_memdel((void**)del);
	}
}

int			ek(t_lemin *lemin)
{
	int				tmp;
	unsigned int	max;
	t_allpaths		*tmp1;

	tmp = 1;
	lemin->matrix = memalloc_matrix(lemin->cnt);
	lemin->container = memalloc_allpaths();
	tmp1 = lemin->container;
	lemin->max_steps = INT_MAX;
	while (bfs(lemin) != 0 && tmp && (lemin->state & S_END))
	{
		backtrack(lemin);
		tmp = nbr_steps(lemin, tmp1, max = 0);
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
	delete_node(lemin, lemin->container);
	delete_extra_node(lemin, lemin->container);
	return (SUCCESS);
}
