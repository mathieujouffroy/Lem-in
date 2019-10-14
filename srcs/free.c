/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:40:11 by yabecret          #+#    #+#             */
/*   Updated: 2019/09/26 12:03:51 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			freegraph(t_graph **room)
{
	if (!(*room))
		return (FAILURE);
	freelinks(&((*room)->links));
	ft_memdel((void **)&(*room));
	return (SUCCESS);
}

int			freelinks(t_links **links)
{
	if (!(*links))
		return (FAILURE);
	freelinks(&((*links)->next));
	ft_memdel((void **)&(*links));
	return (SUCCESS);
}

int 		freeallpaths(t_allpaths **allpaths)
{
	if (!(*allpaths))
		return (FAILURE);
	freeallpaths(&((*allpaths)->next));
	freelinks(&((*allpaths)->path));
	ft_memdel((void**)&(*allpaths));
	return (SUCCESS);
}

void 		freelemin(t_lemin *lemin)
{
	if (lemin->start)
		ft_strdel(&lemin->start);
	if (lemin->end)
		ft_strdel(&lemin->end);
	if (lemin->list)
		freelinks(&lemin->list);
	//ft_printf("list done\n");
	if (lemin->container)
		freeallpaths(&lemin->container);
	//ft_printf("container done\n");
}
