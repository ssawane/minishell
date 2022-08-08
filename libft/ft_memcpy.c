/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:05:01 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:31:32 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*p;

	t = (unsigned char *)src;
	p = (unsigned char *)dst;
	i = 0;
	if (n == 0 || dst == src)
		return (dst);
	while (n > 0)
	{
		p[i] = t[i];
		i++;
		n--;
	}
	return (dst);
}
