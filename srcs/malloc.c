/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:09:53 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/26 11:49:37 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph			*memalloc_graph(void)
{
	t_graph *room;

	if ((room = (t_graph*)ft_memalloc(sizeof(t_graph))) == NULL)
		return (FAILURE);
	return (room);
}

t_links			*memalloc_links(void)
{
	t_links	*elem;

	if ((elem = (t_links*)ft_memalloc(sizeof(t_links))) == NULL)
		return (FAILURE);
	return (elem);
}

t_allpaths		*memalloc_allpaths(void)
{
	t_allpaths	*elem;

	if ((elem = (t_allpaths*)ft_memalloc(sizeof(t_allpaths))) == NULL)
		return (FAILURE);
	return (elem);
}

int				**memalloc_matrix(int size)
{
	int **matrix;
	int cnt;

	cnt = 0;
	if ((matrix = (int**)ft_memalloc(sizeof(int*) * size)) == NULL)
		return (FAILURE);
	while (cnt < size)
	{
		if ((matrix[cnt] = (int*)ft_memalloc(sizeof(int) * size)) == NULL)
			return (FAILURE);
		cnt++;
	}
	return (matrix);
}
