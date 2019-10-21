/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:10:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/21 15:54:39 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				main(void)
{
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(t_lemin));
	ft_printf("size of t_graph is %lu\n", sizeof(t_graph));
	ft_printf("size of t_links is %lu\n", sizeof(t_links));
	ft_printf("size of t_allpaths is %lu\n", sizeof(t_allpaths));
	if (!(parsing(&lemin)))
	{
		freedata(&lemin);
		return (FAILURE);
	}
	if (lemin.head == NULL)
	{
	//	freedata(&lemin);
		return (FAILURE);
	}
	ek(&lemin);
	updatefinalmatrices(&lemin);
	get_final_paths(&lemin);
	solve_lemin(&lemin, 1);
	freelemin(&lemin);
	return (0);
}
