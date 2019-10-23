/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:10:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/23 10:43:44 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				check_argument(t_lemin *lemin, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if ((ft_strcmp(av[i], "-c") == 0) || (ft_strcmp(av[i], "-s") == 0))
		{
			if (ft_strcmp(av[i], "-c") == 0)
				lemin->state |= S_COLOR;
			else
				lemin->state |= S_STEPS;
		}
		else
		{
			ft_printf("{red}ERROR:{reset} only -c and -s allowed\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int				main(int ac, char **av)
{
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(t_lemin));
	lemin.c_id = 1;
	if (ac > 3)
	{
		ft_printf("{red}ERROR:{reset} too much arguments\n");
		return (FAILURE);
	}
	else if (ac > 1 && ac <= 3)
		if (!check_argument(&lemin, ac, av))
			return (FAILURE);
	if (!parsing(&lemin) || !ek(&lemin))
	{
		freedata(&lemin);
		return (FAILURE);
	}
	updatefinalmatrices(&lemin);
	get_final_paths(&lemin, 0);
	ft_printf("%s\n", lemin.map);
	solve_lemin(&lemin, 1);
	freelemin(&lemin);
	return (0);
}
