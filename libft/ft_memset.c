/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:05:09 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:05:10 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	char	*f;
	size_t	i;

	f = (char *)memptr;
	i = 0;
	while (i < num)
	{
		f[i] = val;
		i++;
	}
	return (memptr);
}
