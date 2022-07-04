/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:05:57 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:32:28 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*st;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	st = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (st == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		st[i] = f(i, s[i]);
		i++;
	}
	st[i] = '\0';
	return (st);
}
