/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:03:53 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:03:55 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;
	size_t	i;

	i = nmemb * size;
	str = malloc(i);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, i);
	return (str);
}
