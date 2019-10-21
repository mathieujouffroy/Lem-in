/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_ek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:20:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/17 11:13:59 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			len_max2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	len_max;
	unsigned int	cnt;
	t_allpaths		*tmp;
	int i = 0;

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
	unsigned int	total;
	unsigned int	max_steps;
	unsigned int	max_len;
	t_allpaths		*tmp;
	int i = 0;

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

unsigned int			nbr_steps2(t_lemin *lemin, t_allpaths *head, int index, unsigned int max)
{
	unsigned int	max_steps;
	//unsigned int	max = 0;
	unsigned int	total;
	unsigned int	remainder;
	unsigned int	reste;
	int i = 0;
	t_allpaths		*tmp;

	max_steps = lemin->max_steps1;
	tmp = head;
	total = get_total2(lemin, tmp, index);
	if (total > lemin->nb_ants)
		return (0);
	remainder = (lemin->nb_ants - total) / lemin->nb_pathsek;
	reste = lemin->nb_ants - (remainder * lemin->nb_pathsek + total);
	while (i < index)
	{
		tmp->max_steps += (remainder + tmp->len + (reste ? 1 : 0) - 1);
		if (max < tmp->max_steps)
			max = tmp->max_steps;

		// line below useful if delete same in solve
		lemin->path_max_lenek = tmp->len;
		tmp = tmp->next;
		i++;
		if (reste > 0)
			reste--;
	}
	max_steps = max;
	if (max_steps > lemin->max_steps1)
	// maybe add ants at this moment
		return (0);
	else
		return (max_steps);
}

int			max_stepsek(t_lemin *lemin, t_allpaths *head)
{
	int				nb_paths;
	int				tmp = 1;
	int				max_paths = lemin->nb_pathsek;
	unsigned int	max;

	nb_paths = 1;
	lemin->max_steps1 = INT_MAX;
	while (nb_paths < (max_paths + 1))
	{
		if ((tmp = nbr_steps2(lemin, head, nb_paths, max = 0)) == 0)
		{
			lemin->nb_pathsek = nb_paths - 1;
			return (0);
		}
		else
			lemin->max_steps1 = tmp;
		nb_paths++;
		//lemin->path_max_len = head->len;    // beware if container is better than container 1 need to change
	}
	return (1);
}
