/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:03:48 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/23 11:03:56 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelfirst(t_list **alst)
{
	t_list *todelete;

	if (!alst)
		return ;
	todelete = alst;
	alst = (*alst)->next;
	ft_memdel((void*)todelete);
}
