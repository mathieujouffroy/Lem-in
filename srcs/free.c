/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:40:11 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/17 17:18:20 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			freegraph(t_graph **room)
{
	if (!(*room))
		return (FAILURE);
	//freelinks(&((*room)->links));
	ft_memdel((void **)&(*room));
	return (SUCCESS);
}

/*int 		freeallpaths(t_allpaths **allpaths)
{
	if (!(*allpaths))
		return (FAILURE);
	freeallpaths(&((*allpaths)->next));
	freelinks(&((*allpaths)->path));
	ft_memdel((void**)&(*allpaths));
	return (SUCCESS);
}*/

int 		freeallpaths(t_allpaths *allpaths)
{
	t_allpaths *next;
	
	if (!(allpaths))
		return (FAILURE);
	while (allpaths)
	{
		next = allpaths->next;
		free(allpaths);
	//	free(allpaths);
		allpaths = next;
	}
	return (SUCCESS);
}

int			freeroomlinks(t_links *list, int i)
{
	if (!(list))
		return (FAILURE);
	while (list)
	{
		freelist(list->room->links, i);
		list = list->next;
	}
	return (SUCCESS);
}

int			freelist(t_links *links, int i)
{
	t_links *next;

	if (!(links))
		return (FAILURE);
	while (links)
	{
		next = links->next;
		if (i == 1)
		{
			ft_strdel(&links->room->name);
			ft_strdel(&links->room->parent);
			free(links->room);
		}
		free(links);
		links = next;
	}
	return (SUCCESS);
}

int			freedata(t_lemin *lemin)
{
	int		i;
	
	if (lemin->map)
		ft_strdel(&lemin->map);	
	if (lemin->list)
	{
		freeroomlinks(lemin->list, i = 0);
		freelist(lemin->list, i = 1);  
	}
	return (SUCCESS);
}

void 		freelemin(t_lemin *lemin)
{
	freedata(lemin);
	if (lemin->container1)
	{
		freeallpaths(lemin->container1);
	}
	if (lemin->container)
	{
		freeallpaths(lemin->container);
	}
	//ft_printf("container done\n");
}
