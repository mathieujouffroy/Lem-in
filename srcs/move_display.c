/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:59:58 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/21 20:02:41 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				move_ants(t_lemin *lemin, t_allpaths *paths)
{
	t_links			*tmp;
	unsigned int	tracker;
	unsigned int	current;
	unsigned int	next;

	tmp = paths->path;
	(tmp->room->hash == lemin->hashstart) ? (tmp = tmp->next) : 0;
	current = 0;
	next = 0;
	tracker = 0;
	while (tmp)
	{
		current = tmp->room->antid;
		tmp->room->antid = tracker;
		if (tmp->next)
			next = tmp->next->room->antid;
		tracker = current;
		tmp = tmp->next;
	}
}

void				fill_ants(t_lemin *lemin, t_allpaths *paths)
{
	t_links			*tmp;

	tmp = paths->path;
	tmp = tmp->next;
	if (tmp->room->antid == 0 && paths->nb_ants != 0)
	{
		tmp->room->antid = lemin->ant_state;
		lemin->ant_state++;
		paths->nb_ants--;
	}
}

int					is_empty(t_allpaths *path)
{
	t_links			*tmp;

	tmp = path->path;
	while (tmp)
	{
		if (tmp->room->antid != 0)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int					display_ants(t_lemin *lemin, t_allpaths *paths, int left)
{
	t_links			*tmp;

	tmp = paths->path;
	if (lemin->state & S_COLOR)
		return (display_color_ants(tmp, paths->color_id, left));
	while (tmp)
	{
		if (tmp->room->antid && left == 0)
		{
			ft_printf("L%u-%s", tmp->room->antid, tmp->room->name);
			left = 1;
		}
		else if (tmp->room->antid && left == 1)
			ft_printf(" L%u-%s", tmp->room->antid, tmp->room->name);
		tmp = tmp->next;
	}
	return (left);
}

int					move_and_display(t_lemin *lemin, t_allpaths *path)
{
	unsigned int	i;
	int				ret;
	static int		left;
	t_allpaths		*tmp;

	i = 0;
	left = 0;
	tmp = path;
	ret = 0;
	while (i < lemin->nb_paths)
	{
		move_ants(lemin, tmp);
		fill_ants(lemin, tmp);
		left = display_ants(lemin, tmp, left);
		ret = (is_empty(tmp) == 0) ? 1 : ret;
		tmp = tmp->next;
		i++;
	}
	ret == 1 ? ft_printf("\n") : 0;
	return (ret);
}
