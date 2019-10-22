/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants_and_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:03:40 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/23 00:35:56 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_str_is_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0' ? SUCCESS : FAILURE);
}

int		get_ants(t_lemin *lemin, char *line)
{
	lemin->nb_ants = ft_atoi(line);
	if (lemin->nb_ants > INT_MAX)
	{
		ft_printf("{red}ERROR:{reset} ants overflow\n");
		return (gnl_exit(line));
	}
	add_line_and_delete(lemin, line);
	return (SUCCESS);
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
