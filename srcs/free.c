/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:40:11 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/21 16:21:45 by mjouffro         ###   ########.fr       */
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
	int i = 1;
	//t_allpaths *tmp;
	
	if (!(allpaths))
		return (FAILURE);
	//tmp = allpaths;
	while (allpaths)
	{
		next = allpaths->next;
		ft_printf("new : %d\n", i++);
		//ft_printf("head name is %s:\n", allpaths->path->room->name);
	//	print(allpaths->path);
		freelist(allpaths->path, 0);
		free(allpaths);
		//allpaths->path ? print(allpaths->path) : 0;
		allpaths = next;
	}
	/*allpaths = tmp;
	while (tmp)
	{
		next = tmp->next;
	//	freelist(tmp->path, 0);
		ft_printf("new\n");
		print(tmp->path);
		free(tmp);
		//tmp->path ? print(tmp->path) : 0;
		tmp = next;
	}*/
	free(allpaths);
	//ft_memdel((void**)allpaths);
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
	free(list);
	return (SUCCESS);
}

int			freelist(t_links *links, int i)
{
	t_links *next;

	if (!(links))
	{
		ft_printf("FAILURE\n");
		return (FAILURE);
	}
	while (links)
	{
		/*if (links && links->next)
			next = links->next;
		else
		{
			return (SUCCESS);
		}*/
		next = links->next;
		if (i == 1)
		{
			ft_strdel(&links->room->name);
			free(links->room);
		}
		ft_printf("room name is %s\n", links->room->name);
		//ft_printf("now free links\n");
		free(links);
		links = next;
	}
//	free(links);
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
	//free(lemin->list->room);
	return (SUCCESS);
}

int		freematrix(t_lemin *lemin)
{
	int i;

	i = 0;
	while (i < lemin->cnt)
	{
		//ft_printf("%d\n", lemin->matrix[i][0]);
		ft_memdel((void**)(lemin->matrix[i++]));
	}
	free(lemin->matrix);
	return (0);
}


void 		freelemin(t_lemin *lemin)
{
	int i = 0;

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
	ft_printf("{green}NOW FREE DATA{reset}\n");
	freedata(lemin);
}
