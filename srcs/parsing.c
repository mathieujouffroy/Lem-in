/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:08:48 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/23 10:30:09 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		gnl_exit(char *line)
{
	ft_strdel(&line);
	return (0);
}

int		success_exit(char *line)
{
	ft_strdel(&line);
	return (1);
}

void	add_line_and_delete(t_lemin *lemin, char *line)
{
	add_line_to_str(lemin, line);
	ft_strdel(&line);
}

int		is_data_sufficient(t_lemin *lemin)
{
	if (!(lemin->state & S_LINKS) || !(lemin->state & S_START)
	|| !(lemin->state & S_END) || !lemin->nb_ants)
	{
		ft_printf("{red}ERROR:{reset} not enough data : ");
		ft_printf("missing source, sink, links or ants\n");
		return (0);
	}
	return (1);
}

int		parsing(t_lemin *lemin)
{
	char		*line;
	int			failure;

	line = NULL;
	failure = 1;
	while (get_next_line(FD, &line) == 1)
	{
		if (failure && is_command(line))
			add_command_to_state(lemin, line);
		else if (failure && is_comment(line))
			add_line_and_delete(lemin, line);
		else if (failure && ft_str_is_digit(line) && !lemin->nb_ants)
			(!get_ants(lemin, line)) ? failure = 0 : 0;
		else if (failure && links_formatting(lemin, line))
			(!parse_links(lemin, line)) ? failure = 0 : 0;
		else if (failure && !(lemin->state & S_LINKS) && (lemin->nb_ants))
			(!parse_room(lemin, line)) ? failure = 0 : 0;
		else
			ft_strdel(&line);
	}
	return (failure ? is_data_sufficient(lemin) : FAILURE);
}
