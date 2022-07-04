/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:06:09 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:06:09 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	f;

	f = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[f]);
	while (s[--f] != (unsigned char)c)
	{
		if (f <= 0)
			return (0);
		if (!s[f])
			return (0);
	}
	return ((char *)&s[f]);
}
