/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:45:00 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/21 17:41:10 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


void	add_line_to_str(t_lemin *lemin, char *str)
{
	char *tmp;

	str = ft_strjoin(str, "\n");
	tmp = lemin->map;
	if (lemin->map == NULL)
		lemin->map = ft_strdup(str);
	else
		lemin->map = ft_strjoin(tmp, str);
	free(tmp);
	ft_strdel(&str);
}

void	addlinks(t_links **links, t_links *new)
{
	new->next = (*links);
	*links = new;
}

void printall(t_links *tmp)
{
	if (!tmp)
	{
		ft_printf("not tmp\n");
		return ;
	}
	while (tmp)
	{
		ft_printf("{red}head is :%s\n{reset}", tmp->room->name);
		ft_printf("{yellow}hash is :%lu\n{reset}", tmp->room->hash);
	//	ft_printf("{yellow}pred is :%lu\n{reset}", tmp->room->pred);
		ft_printf("{yellow}pare is :%s\n{reset}", tmp->room->parent);
		ft_printf("{violet}index is :%d\n{reset}", tmp->room->index);
		if (tmp->room->links)
			print(tmp->room->links);
		tmp = tmp->next;
	}
}

void print(t_links *head)
{
	if (!head)
	{
		ft_printf("not tmp\n");
		return ;
	}
	while (head != NULL)
	{
		ft_printf("in the loooooop\n");
		head->room->name ? ft_printf("{green}room is :%s\n{reset}", head->room->name) : 0;
		/*if (head->room->links)
		{
			ft_printf("room has links\n");
			print(head->room->links);
		}*/

		head = head->next;
	}
}

void printmatrix(int **matrix, int size)
{
	int x;
	int y;

	x = 0;
	ft_printf("   ");
	if (matrix != NULL)
	{
		while (x < size)
		{
			ft_printf("{green}%d{reset}|", x);
			x++;
		}
		x = 0;
		ft_printf("\n");
		while (x < size)
		{
			y = 0;
			ft_printf("{green}%d{reset} |", x);
			while (y < size)
			{
				if (matrix[x][y] == 0)
					ft_printf("%d|", matrix[x][y]);
				else
					ft_printf("{red}%d{reset}|", matrix[x][y]);
				y++;
			}
			ft_printf("\n");
			x++;
		}
	}
}

unsigned long hashing(unsigned char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}
