/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:02:25 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/23 10:44:29 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int					check_coord(char **rooms)
{
	int		i;
	long	res;

	i = 0;
	if (!rooms[0] || !rooms[1] || !rooms[2])
	{
		free_tab(rooms);
		return (FAILURE);
	}
	while (i < 2)
	{
		res = ft_atoll(rooms[i + 1]);
		if (res > INT_MAX || res < INT_MIN)
		{
			free_tab(rooms);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int					ft_cntchr(char *str, char c)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}

int					display_color_ants(t_links *tmp, int id, int left)
{
	while (tmp)
	{
		if (tmp->room->antid && left == 0)
		{
			ft_printf("\033[1;3%dmL%u{reset}-%s",
			id, tmp->room->antid, tmp->room->name);
			left = 1;
		}
		else if (tmp->room->antid && left == 1)
			ft_printf(" \033[1;3%dmL%u{reset}-%s",
			id, tmp->room->antid, tmp->room->name);
		tmp = tmp->next;
	}
	return (left);
}
