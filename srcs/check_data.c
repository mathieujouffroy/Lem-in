/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:10:25 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/26 11:48:45 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_comment(char *line)
{
	if (line && (line[0] == '#'))
		return (SUCCESS);
	return (FAILURE);
}

int		is_command(char *line)
{
	if (is_comment(line) && line[1] == '#')
		return (SUCCESS);
	return (FAILURE);
}

int		is_start(t_lemin *lemin)
{
	if (lemin->state & S_START)
	{
		lemin->state &= ~S_START;
		return (1);
	}
	return (0);
}

int		is_end(t_lemin *lemin)
{
	if (lemin->state & S_END)
	{
		lemin->state &= ~S_END;
		return (1);
	}
	return (0);
}

int		is_hash_existing(t_links *tmp, unsigned long hash)
{
	while (tmp)
	{
		if (tmp->room->hash == hash)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		are_hash_valid(t_links *tmp, unsigned long *h)
{
	int state;

	state = 0;
	while (tmp)
	{
		if (!(state & S_R1) && (tmp->room->hash == h[0]))
			state |= S_R1;
		else if (!(state & S_R2) && (tmp->room->hash == h[1]))
			state |= S_R2;
		tmp = tmp->next;
	}
	return (((state & S_R1) && (state & S_R2)) ? SUCCESS : FAILURE);
}
