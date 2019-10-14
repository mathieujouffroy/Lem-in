/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:04:41 by yabecret          #+#    #+#             */
/*   Updated: 2019/04/03 16:05:09 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_atoll(char *s)
{
	intmax_t	res;
	int			i;

	i = 0;
	res = 0;
	while (s[i] && ft_isdigit(s[i]))
	{
		res += s[i] - 48;
		if (ft_isdigit(s[i + 1]))
			res *= 10;
		i++;
	}
	return (res);
}
