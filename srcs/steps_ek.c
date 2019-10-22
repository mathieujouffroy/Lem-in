/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_ek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:20:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 21:48:32 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						len_max2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int		len_max;
	unsigned int		cnt;
	t_allpaths			*tmp;
	int					i;

	i = 0;
	cnt = 0;
	tmp = head;
	len_max = tmp->len;
	while (i < index)
	{
		len_max = len_max < tmp->len ? tmp->len : len_max;
		cnt++;
		tmp = tmp->next;
		i++;
	}
	lemin->nb_pathsek = cnt;
	return (len_max);
}

unsigned int			get_total2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int		total;
	unsigned int		max_steps;
	unsigned int		max_len;
	t_allpaths			*tmp;
	int					i;

	i = 0;
	tmp = head;
	max_len = len_max2(lemin, tmp, index);
	total = 0;
	max_steps = lemin->max_steps1;
	while (i < index)
	{
		tmp->max_steps = ((max_len + 1) - tmp->len);
		total += tmp->max_steps;
		tmp = tmp->next;
		i++;
	}
	return (total);
}

unsigned int			max_steps_comparison(t_lemin *lemin, unsigned int max,
											unsigned int max_steps)
{
	max_steps = max;
	if (max_steps > lemin->max_steps1)
		return (0);
	else
		return (max_steps);
}

unsigned int			nbr_steps2(t_lemin *lemin, t_allpaths *head,
									int index, unsigned int max)
{
	unsigned int		max_steps;
	unsigned int		total;
	int					i;
	t_allpaths			*tmp;

	i = 0;
	max_steps = lemin->max_steps1;
	tmp = head;
	total = get_total2(lemin, tmp, index);
	if (total > lemin->nb_ants)
		return (0);
	remainder_and_reste_calculus_ek(lemin, total);
	while (i < index)
	{
		tmp->max_steps += max_steps_calculus_ek(lemin, tmp->len);
		(max < tmp->max_steps) ? (max = tmp->max_steps) : 0;
		lemin->path_max_lenek = tmp->len;
		(lemin->remainder_ek > 0) ? (lemin->remainder_ek--) : 0;
		i++;
		tmp = tmp->next;
	}
	return (max_steps_comparison(lemin, max, max_steps));
}

int						max_stepsek(t_lemin *lemin, t_allpaths *head)
{
	int					nb_paths;
	int					tmp;
	int					max_paths;
	unsigned int		max;

	nb_paths = 1;
	tmp = 1;
	max_paths = lemin->nb_pathsek;
	lemin->max_steps1 = UINT_MAX;
	while (nb_paths < (max_paths + 1))
	{
		max = 0;
		tmp = nbr_steps2(lemin, head, nb_paths, max);
		if (tmp == 0)
		{
			lemin->nb_pathsek = nb_paths - 1;
			return (0);
		}
		else
			lemin->max_steps1 = tmp;
		nb_paths++;
	}
	return (1);
}
