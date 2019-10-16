/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:41:26 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/16 12:29:42 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int res;
	int nega;
	int i;

	i = 0;
	nega = 1;
	while (ft_iswhitespace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			nega = -1;
	}
	res = 0;
	while (s[i] && ft_isdigit(s[i]))
	{
		if (res > INT_MAX / 10 || ((res == INT_MAX / 10) && (s[i] - 48 > 8)) || res == INT_MIN)
			return (0);	
		res += s[i] - 48;
		if (ft_isdigit(s[i + 1]))
			res *= 10;
		i++;
	}
	return (res * nega);
}
