/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants_and_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:03:40 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/21 20:04:11 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_str_is_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0' ? SUCCESS : FAILURE);
}

void	get_ants(t_lemin *lemin, char *line)
{
	lemin->nb_ants = ft_atoi(line);
	add_line_and_delete(lemin, line);
}

int		start_end(char *line)
{
	if (ft_strcmp("##start", line) == 0)
		return (S_START);
	else if (ft_strcmp("##end", line) == 0)
		return (S_END);
	return (FAILURE);
}

void	add_command_to_state(t_lemin *lemin, char *line)
{
	lemin->state |= start_end(line);
	add_line_and_delete(lemin, line);
}
