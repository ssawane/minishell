/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:06:13 by ssawane           #+#    #+#             */
/*   Updated: 2021/10/21 17:06:14 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 0;
	if (!s1)
		return (NULL);
	while (ft_strchr(set, s1[i]) && *s1)
		s1++;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len]) && len)
		len--;
	return (ft_substr(s1, 0, len + 1));
}
