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