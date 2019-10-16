/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:10:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/16 12:06:30 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				main(void)
{
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(lemin));
	if (!(parsing(&lemin)))
		return (FAILURE);
	if (lemin.head == NULL)
		return (FAILURE);
	ek(&lemin);
	updatefinalmatrices(&lemin);
	get_final_paths(&lemin);
	//ft_printf("%s\n", lemin.map);
	solve_lemin(&lemin, 1);
	freelemin(&lemin);
//	freeallpaths(&lemin.container);
//	freeallpaths(&lemin.container1);
//	while (1);
	return (0);
}
