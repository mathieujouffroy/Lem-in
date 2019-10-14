/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:32:49 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/14 16:01:06 by mjouffro         ###   ########.fr       */
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
	ft_printf("rooms error\n");
	return (gnl_exit(line));
}

int		exit_with_message_links(char *line)
{
	ft_printf("links error\n");
	return (gnl_exit(line));
}