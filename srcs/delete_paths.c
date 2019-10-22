/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:04:25 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 15:51:03 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				delete_extra_node(t_lemin *lemin, t_allpaths *head)
{
	t_allpaths		*nodebeforedel;
	t_allpaths		*del;

	del = head;
	nodebeforedel = head;
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
	}
}

void				delete_path_too_big(t_lemin *lemin, t_allpaths *head)
{
	t_allpaths		*nodebeforedel;
	t_allpaths		*del;

	del = head;
	nodebeforedel = head;
	while (del->next != NULL)
	{
		nodebeforedel = del;
		del = del->next;
	}
	if (del->len > lemin->max_steps)
	{
		nodebeforedel->next = NULL;
		lemin->nb_pathsbfs > 1 ? lemin->nb_pathsbfs-- : 0;
		freeallpaths(del);
	}
}
