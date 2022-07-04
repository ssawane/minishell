/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:05:05 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:31:41 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tdst;
	unsigned char	*tsrc;
	size_t			i;

	i = 0;
	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	tdst = (unsigned char *)dst;
	tsrc = (unsigned char *)src;
	if (tdst < tsrc)
	{
		while (i < len)
		{
			tdst[i] = tsrc[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			tdst[len] = tsrc[len];
	}
	return (tdst);
}
