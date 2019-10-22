/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:19:27 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 15:01:28 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					len_max(t_lemin *lemin, t_allpaths *head)
{
	unsigned int	len_max;
	unsigned int	cnt;
	t_allpaths		*tmp;

	cnt = 0;
	tmp = head;
	len_max = tmp->len;
	while (tmp)
	{
		len_max = len_max < tmp->len ? tmp->len : len_max;
		cnt++;
		tmp = tmp->next;
	}
	lemin->nb_pathsbfs = cnt;
	return (len_max);
}

unsigned int		get_total(t_lemin *lemin, t_allpaths *head)
{
	unsigned int	total;
	unsigned int	max_steps;
	unsigned int	max_len;
	t_allpaths		*tmp;

	tmp = head;
	max_len = len_max(lemin, tmp);
	total = 0;
	max_steps = lemin->max_steps;
	while (tmp)
	{
		tmp->max_steps = ((max_len + 1) - tmp->len);
		total += tmp->max_steps;
		tmp = tmp->next;
	}
	return (total);
}

int					is_path_len(t_allpaths *tmp)
{
	if (tmp->len == 0)
	{
		ft_printf("{red}ERROR: Inf Loop\n");
		return (0);
	}
	return (1);
}

unsigned int		nbr_steps(t_lemin *lemin, t_allpaths *head,
					unsigned int max)
{
	unsigned int	max_steps;
	t_allpaths		*tmp;

	max_steps = lemin->max_steps;
	tmp = head;
	if (!is_path_len(tmp))
		return (-1);
	lemin->total = get_total(lemin, tmp);
	if (lemin->total > lemin->nb_ants)
		return (0);
	remainder_and_reste_calculus(lemin);
	while (tmp)
	{
		tmp->max_steps += max_steps_calculus(lemin, tmp->len);
		(max < tmp->max_steps) ? (max = tmp->max_steps) : 0;
		lemin->path_max_lenbfs = tmp->len;
		(lemin->reste > 0) ? (lemin->reste--) : 0;
		tmp = tmp->next;
	}
	max_steps = max;
	if (max_steps > lemin->max_steps)
		return (0);
	else
		return (max_steps);
}
