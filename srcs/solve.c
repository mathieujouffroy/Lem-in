/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:08:13 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 15:49:50 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_allpaths			*final_solution(t_lemin *lemin)
{
	t_allpaths		*tmp;

	tmp = NULL;
	if (lemin->max_steps < lemin->max_steps1)
	{
		tmp = lemin->container;
		lemin->nb_paths = lemin->nb_pathsbfs;
		lemin->path_max_len = lemin->path_max_lenbfs;
	}
	else if (lemin->max_steps >= lemin->max_steps1)
	{
		tmp = lemin->container1;
		lemin->nb_paths = lemin->nb_pathsek;
		lemin->max_steps = lemin->max_steps1;
		lemin->path_max_len = lemin->path_max_lenek;
	}
	return (tmp);
}

t_allpaths			*ants_first_step(t_lemin *lemin, t_allpaths *head)
{
	t_allpaths		*tmp;
	unsigned int	i;

	i = 0;
	tmp = head;
	while (tmp && i < lemin->nb_paths)
	{
		tmp->nb_ants = (lemin->path_max_len - tmp->len + 1);
		lemin->total += tmp->nb_ants;
		tmp = tmp->next;
		i++;
	}
	tmp = head;
	return (tmp);
}

int					ants_per_path(t_lemin *lemin, t_allpaths *head)
{
	t_allpaths		*tmp;
	unsigned int	i;
	int				remainder;
	int				reste;

	lemin->total = 0;
	remainder = 0;
	tmp = ants_first_step(lemin, head);
	remainder = (lemin->nb_ants - lemin->total) / lemin->nb_paths;
	reste = lemin->nb_ants - (remainder * lemin->nb_paths) - lemin->total;
	i = 0;
	while (tmp && i < lemin->nb_paths)
	{
		tmp->nb_ants += remainder;
		tmp->nb_ants += reste ? 1 : 0;
		reste > 0 ? reste-- : 0;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int					solve_lemin(t_lemin *lemin, unsigned int move)
{
	t_allpaths		*head;
	t_allpaths		*tmp;

	head = final_solution(lemin);
	tmp = head;
	ants_per_path(lemin, tmp);
	move = 1;
	lemin->ant_state = 1;
	while (move <= lemin->max_steps)
		move += move_and_display(lemin, head);
	if (lemin->state & S_STEPS)
		ft_printf("\nOur nbr of steps : {red}%u\n{reset}", lemin->max_steps);
	return (1);
}
