/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:57:55 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 16:32:51 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned int		max_steps_calculus(t_lemin *lemin, unsigned int len)
{
	unsigned		n;

	n = (lemin->remainder + len + (lemin->reste ? 1 : 0) - 1);
	return (n);
}

void				remainder_and_reste_calculus(t_lemin *lemin)
{
	lemin->remainder = (lemin->nb_ants - lemin->total) / lemin->nb_pathsbfs;
	lemin->reste = lemin->nb_ants
					- (lemin->remainder * lemin->nb_pathsbfs + lemin->total);
}

unsigned int		max_steps_calculus_ek(t_lemin *lemin, unsigned int len)
{
	unsigned		n;

	n = (lemin->remainder_ek + len + (lemin->reste_ek ? 1 : 0) - 1);
	return (n);
}

void				remainder_and_reste_calculus_ek(t_lemin *lemin,
													unsigned int total)
{
	lemin->remainder_ek = (lemin->nb_ants - total) / lemin->nb_pathsek;
	lemin->reste_ek = lemin->nb_ants
					- (lemin->remainder_ek * lemin->nb_pathsek + total);
}
