/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:32:49 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/22 13:20:02 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		rooms_errors(t_lemin *lemin)
{
	if (!(lemin->state & S_ROOMS))
		return (SUCCESS);
	if (lemin->start == NULL || lemin->end == NULL)
		return (SUCCESS);
	return (FAILURE);
}

int		exit_with_message_room(char *line)
{
	ft_printf("{red}ERROR:{reset} room format\n");
	return (gnl_exit(line));
}

int		exit_with_message_coord_overflow(char *line)
{
	ft_printf("{red}ERROR:{reset} coord overflow\n");
	return (gnl_exit(line));
}

int		exit_with_message_room_duplicate(char *line)
{
	ft_printf("{red}ERROR:{reset} duplicate room\n");
	return (gnl_exit(line));
}

int		exit_with_message_links(char *line)
{
	ft_printf("{red}ERROR:{reset} links format\n");
	return (gnl_exit(line));
}
