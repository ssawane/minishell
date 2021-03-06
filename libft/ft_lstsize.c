/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:04:51 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:25:30 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	k;

	k = 1;
	if (!lst)
		return (0);
	while (lst -> next)
	{
		lst = lst -> next;
		k++;
	}
	return (k);
}
