/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:01:43 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:24:50 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)-> content);
		p = *lst;
		*lst = p -> next;
		free(p);
	}
	lst = NULL;
}
