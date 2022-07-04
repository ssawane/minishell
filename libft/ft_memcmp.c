/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:04:58 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:04:58 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	int				i;
	unsigned char	*tb1;
	unsigned char	*tb2;

	i = 0;
	tb1 = (unsigned char *)b1;
	tb2 = (unsigned char *)b2;
	while (len > 0)
	{
		if (tb1[i] != tb2[i])
			return (tb1[i] - tb2[i]);
		i++;
		len--;
	}
	return (0);
}
