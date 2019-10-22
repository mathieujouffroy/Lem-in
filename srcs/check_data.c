/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:10:25 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 15:55:06 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_comment(char *line)
{
	if (line && (line[0] == '#'))
		return (SUCCESS);
	return (FAILURE);
}

int			is_command(char *line)
{
	if (is_comment(line) && line[1] == '#')
		return (SUCCESS);
	return (FAILURE);
}

int			is_start(t_lemin *lemin)
{
	if (lemin->state & S_START)
	{
		lemin->state &= ~S_START;
		return (1);
	}
	return (0);
}

int			is_end(t_lemin *lemin)
{
	if (lemin->state & S_END)
	{
		lemin->state &= ~S_END;
		return (1);
	}
	return (0);
}

int			is_room(char *line)
{
	int		i;
	int		failure;

	i = 0;
	failure = 0;
	while (line[i] != '\0')
	{
		(line[0] == ' ' || line[0] == 'L' || line[0] == '#') ? failure = 1 : 0;
		while ((line[i] >= 33) && (line[i] <= 126) && (line[i] != 45))
			i++;
		(line[i] != ' ') ? failure = 1 : i++;
		if (line[i] == '-' || line[i] == '+')
			i++;
		while (*line && ft_isdigit(line[i]))
			i++;
		(line[i] != ' ') ? failure = 1 : i++;
		if (line[i] == '-' || line[i] == '+')
			i++;
		while (*line && ft_isdigit(line[i]))
			i++;
		(line[i] != '\0') ? failure = 1 : 0;
	}
	if (failure == 1)
		return (FAILURE);
	return (SUCCESS);
}
