/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:27:12 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/15 16:09:43 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links		*find_hash_node(t_links *list, unsigned long hash)
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

int			backtrack(t_lemin *lemin)
{
	unsigned long	tracker;
	t_links			*tmp;
	unsigned int	cnt;

	tracker = lemin->hashend;
	cnt = 0;
	//add backward to avoid useless calcul in maxsteps
	if (lemin->state & S_BACKWARD)
	{
		lemin->state &= ~S_BACKWARD;
		lemin->container->backward = 1;
	}
	while (1)
	{
		if (tracker == 0)
		{
			//ft_printf("{yellow} pre-final solution : {reset}\n");
			//print(lemin->container->path);
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
		ft_printf("{yellow}---len 0 : lemin nb paths is %d---\n{reset}", lemin->nb_pathsbfs);
		nodebeforedel->next = NULL;
		lemin->nb_pathsbfs > 1 ? lemin->nb_pathsbfs-- : 0;
		ft_printf("{green}---now lemin nb paths is %d---\n{reset}", lemin->nb_pathsbfs);
		freelinks(&del->path);
		ft_memdel((void**)del);
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
		ft_printf("{yellow}---lemin nb paths is %d---\n{reset}", lemin->nb_pathsbfs);
		nodebeforedel->next = NULL;
		freelinks(&del->path);
		ft_memdel((void**)del);
		ft_printf("{green}---now lemin nb paths is %d---\n{reset}", lemin->nb_pathsbfs);
	}
}

int			ek(t_lemin *lemin)
{
	int				tmp;
	unsigned int	max;
	t_allpaths		*tmp2;
	t_allpaths		*tmp3;

	tmp = 1;
	lemin->matrix = memalloc_matrix(lemin->cnt);
	lemin->container = memalloc_allpaths();
	lemin->debut = lemin->container;


	lemin->container = lemin->debut;

	lemin->max_steps = INT_MAX;
	while (bfs(lemin) != 0 && tmp && (lemin->state & S_END))
	{
		backtrack(lemin);
		tmp = nbr_steps(lemin, lemin->debut, max = 0);

		if (tmp == -1)
			return (FAILURE);
			
		tmp ? lemin->max_steps = tmp : lemin->max_steps;
		// compare if max steps gets bigger get out
		resetvisited(lemin);
		if (!updatematrix(lemin))
			break ;
	}
	//tmp == 0 ? lemin->nb_pathsbfs-- : 0;
	lemin->container = lemin->debut;


	tmp2 = lemin->container;
	while (tmp2)
	{
		ft_printf("tmp len is %d\n", tmp2->len);
		tmp2 = tmp2->next;
	}

	delete_extra_node(lemin, lemin->container);
	delete_node(lemin, lemin->container);

	tmp3 = lemin->container;
	while (tmp3)
	{
		ft_printf("tmp len is %d\n", tmp3->len);
		tmp3 = tmp3->next;
	}

	return (SUCCESS);
}
