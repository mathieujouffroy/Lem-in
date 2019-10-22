/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:02:25 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 23:56:37 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
