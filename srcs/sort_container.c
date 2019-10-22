/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:40:36 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 14:18:00 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_allpaths		*swap_container(t_allpaths *container, t_allpaths *head,
								t_allpaths *pred, t_allpaths *swap2)
{
	t_allpaths	*swap;

	while (container->next)
	{
		if (container->len > container->next->len)
		{
			swap = container;
			container = container->next;
			pred->next = container;
			swap2 = container->next;
			swap->next = swap2;
			container->next = swap;
			(swap == head) ? head = container : 0;
			swap = NULL;
			container = head;
			pred = head;
		}
		else
		{
			(container != head) ? pred = pred->next : 0;
			container = container->next;
		}
	}
	container = head;
	return (container);
}

t_allpaths		*sort_paths(t_allpaths *container)
{
	t_allpaths *pred;
	t_allpaths *head;
	t_allpaths *swap2;

	head = container;
	pred = head;
	swap2 = NULL;
	head = swap_container(container, head, pred, swap2);
	container = head;
	return (container);
}
