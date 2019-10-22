/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:26:52 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 16:42:28 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					find_nb_paths(t_lemin *lemin)
{
	int				ret;
	int				cnt;

	cnt = 0;
	ret = 0;
	while (cnt < lemin->cnt)
	{
		if (lemin->matrix[cnt][lemin->sink->index] == 1)
			ret++;
		cnt++;
	}
	return (ret);
}

t_links				*find_index_node(t_links *list, int index)
{
	t_links			*new;
	t_links			*tmp;

	new = memalloc_links();
	tmp = list;
	while (tmp)
	{
		if (tmp->room && tmp->room->index == index)
		{
			new->room = tmp->room;
			new->next = NULL;
			return (new);
		}
		tmp = tmp->next;
	}
	return (new);
}

int					get_matrix_path(t_lemin *lemin)
{
	t_links			*tmp;
	int				current;
	int				len;
	int				i;

	len = 0;
	current = lemin->sink->index;
	while (current != lemin->head->index)
	{
		i = 0;
		while (i < lemin->cnt && lemin->matrix[i][current] != 1)
			i++;
		if (i == lemin->cnt)
			return (0);
		tmp = find_index_node(lemin->list, i);
		addlinks(&lemin->container1->path, tmp);
		lemin->matrix[i][current] = 0;
		current = i;
		len++;
	}
	return (len);
}

void				sort_and_maxstepsek(t_lemin *lemin)
{
	t_allpaths		*head;
	unsigned int	i;

	lemin->container1 = sort_paths(lemin->container1);
	head = lemin->container1;
	i = 1;
	while (lemin->container1)
	{
		lemin->container1->color_id = i;
		i++;
		if (i == 8)
			i = 1;
		lemin->container1 = lemin->container1->next;
	}
	lemin->container1 = head;
	max_stepsek(lemin, head);
}

void				get_final_paths(t_lemin *lemin, unsigned int i)
{
	t_links			*tmp;
	t_allpaths		*tmp2;
	t_allpaths		*head;
	int				length;

	lemin->nb_pathsek = find_nb_paths(lemin);
	lemin->container1 = memalloc_allpaths();
	head = lemin->container1;
	while (i < lemin->nb_pathsek)
	{
		tmp = memalloc_links();
		tmp->room = lemin->sink;
		addlinks(&lemin->container1->path, tmp);
		length = get_matrix_path(lemin);
		lemin->container1->len = length;
		if (i != lemin->nb_pathsek - 1)
		{
			tmp2 = memalloc_allpaths();
			lemin->container1->next = tmp2;
			lemin->container1 = tmp2;
		}
		i++;
	}
	lemin->container1 = head;
	sort_and_maxstepsek(lemin);
}
