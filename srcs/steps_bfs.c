/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:19:27 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/15 13:43:18 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						len_max(t_lemin *lemin, t_allpaths *head)
{
	unsigned int	len_max;
	unsigned int	cnt;
	t_allpaths		*tmp;

	cnt = 0;
	tmp = head;
	len_max = tmp->len;
	while (tmp)
	{
//		ft_printf("{yellow}nbrsteps len : %d\n{reset}", tmp->len);
//		if (tmp->backward)
//			return (len_max);
		len_max = len_max < tmp->len ? tmp->len : len_max;
		cnt++;
		tmp = tmp->next;
	}
	lemin->nb_pathsbfs = cnt;
	return (len_max);
}

unsigned int			get_total(t_lemin *lemin, t_allpaths *head)
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
//		if (tmp->backward)
//			return (total);
		tmp->max_steps = ((max_len + 1) - tmp->len);
		total += tmp->max_steps;
		tmp = tmp->next;
	}
	return (total);
}

unsigned int			nbr_steps(t_lemin *lemin, t_allpaths *head, unsigned int max)
{
	unsigned int	max_steps;
//	unsigned int	max = 0;
//	unsigned int	total;
//	unsigned int	reste;
//	unsigned int	remainder;
	t_allpaths		*tmp;

	max_steps = lemin->max_steps;
	tmp = head;

	if (tmp->len == 0)
	{
		ft_printf("{red}ERROR: Inf Loop\n");
		return (-1);
	}
/*
	total = get_total(lemin, tmp);
	if (total > lemin->nb_ants)
		return (0);
	remainder = (lemin->nb_ants - total) / lemin->nb_paths;
	reste = lemin->nb_ants - (remainder * lemin->nb_paths + total);
	while (tmp)
	{
		tmp->max_steps += (remainder + tmp->len + (reste ? 1 : 0) - 1);
		if (max < tmp->max_steps)
			max = tmp->max_steps;
		lemin->path_max_len = tmp->len;
		tmp = tmp->next;
		if (reste > 0)
			reste--;
	}
*/
	lemin->total = get_total(lemin, tmp);
	if (lemin->total > lemin->nb_ants)
		return (0);
	lemin->remainder = (lemin->nb_ants - lemin->total) / lemin->nb_pathsbfs;
	lemin->reste = lemin->nb_ants - (lemin->remainder * lemin->nb_pathsbfs + lemin->total);
	while (tmp)
	{
	//	if (tmp->backward)
	//		break ;
		//ft_printf("{red}nbrsteps len : %d\n{reset}", tmp->len);
		//print(tmp2->path);
		//printall(tmp->path);
		tmp->max_steps += (lemin->remainder + tmp->len + (lemin->reste ? 1 : 0) - 1);
		if (max < tmp->max_steps)
			max = tmp->max_steps;
		lemin->path_max_lenbfs = tmp->len;
		tmp = tmp->next;
		if (lemin->reste > 0)
			lemin->reste--;
	}
	max_steps = max;
	if (max_steps > lemin->max_steps)
		return (0);
	else
		return (max_steps);
}
