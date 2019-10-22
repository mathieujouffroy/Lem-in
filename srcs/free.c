/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:40:11 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/22 14:03:47 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				freeallpaths(t_allpaths *allpaths)
{
	t_allpaths *next;

	if (!(allpaths))
		return (FAILURE);
	while (allpaths)
	{
		next = allpaths->next;
		freelist(allpaths->path, 0);
		free(allpaths);
		allpaths = next;
	}
	free(allpaths);
	return (SUCCESS);
}

int				freeroomlinks(t_links *list, int i)
{
	if (!(list))
		return (FAILURE);
	while (list)
	{
		freelist(list->room->links, i);
		list = list->next;
	}
	free(list);
	return (SUCCESS);
}

int				freelist(t_links *links, int i)
{
	t_links		*next;

	if (!(links))
		return (FAILURE);
	while (links)
	{
		next = links->next;
		if (i == 1)
		{
			ft_strdel(&links->room->name);
			free(links->room);
		}
		free(links);
		links = next;
	}
	return (SUCCESS);
}

int				freedata(t_lemin *lemin)
{
	int			i;

	if (lemin->map)
		ft_strdel(&lemin->map);
	if (lemin->list)
	{
		freeroomlinks(lemin->list, i = 0);
		freelist(lemin->list, i = 1);
	}
	return (SUCCESS);
}

void			freelemin(t_lemin *lemin)
{
	int			i;

	i = 0;
	while (i < lemin->cnt)
	{
		free(lemin->matrix[i]);
		lemin->matrix[i] = NULL;
		i++;
	}
	free(lemin->matrix);
	if (lemin->container1)
		freeallpaths(lemin->container1);
	if (lemin->container)
		freeallpaths(lemin->container);
	freedata(lemin);
}
