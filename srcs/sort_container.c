/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:40:36 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/26 16:00:14 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_allpaths	*swap_container(t_allpaths *container, t_allpaths *pred)
{
	t_allpaths *swap;
	t_allpaths *swap2;

	swap = container;
	container = container->next;
	pred->next = container;
	swap2 = container->next;
	swap->next = swap2;
	container->next = swap;
	return (swap);
}

t_allpaths	*sort_paths(t_allpaths *container)
{
	t_allpaths *pred;
	t_allpaths *head;
	t_allpaths *swap;
	t_allpaths *swap2;

	head = container;
	pred = head;
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
			//swap = swap_container(container, pred);
			if (swap == head)
				head = container;
			swap = NULL;
			container = head;
			pred = head;
		}
		else
		{
			if (container != head)
				pred = pred->next;
			container = container->next;
		}
	}
	container = head;
	return (container);
}
