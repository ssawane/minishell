/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_corr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:13:34 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/12 16:13:30 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pointer(int t)
{
	int	p;

	p = t - 2;
	if (p < 0)
		p = -1;
	return (p);
}

char	*quot_del(char *str, int *start, int symb)
{
	int		j;
	int		k;
	int		t;
	char	*new;

	j = 0;
	k = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	t = *start + 1;
	while (str[t] != symb && str[t] != '\0')
			t++;
	while (k <= t)
	{
		if (str[k] == symb && j >= *start)
			k++;
		else
			new[j++] = str[k++];
	}
	while (str[k] != '\0')
		new[j++] = str[k++];
	new[j] = '\0';
	*start = pointer(t);
	free(str);
	return (new);
}

char	*word_from_env2(char *toenv)
{
	char	*fromenv;
	int		i;

	i = -1;
	fromenv = NULL;
	while (shl.envv[++i])
	{
		if (!ft_strncmp(shl.envv[i], toenv, ft_strlen(toenv)))
		{
			fromenv = ft_substr(shl.envv[i], ft_strlen(toenv),
					ft_strlen(shl.envv[i]) - ft_strlen(toenv));
			break ;
		}
	}
	return (fromenv);
}

char	*word_from_env(char *str, int k, int j)
{
	char	*toenv;
	char	*fromenv;
	int		i;

	i = 0;
	fromenv = NULL;
	toenv = (char *)malloc(sizeof(char) * (j - k + 2));
	while (k < j)
		toenv[i++] = str[k++];
	toenv[i++] = '=';
	toenv[i] = '\0';
	if (!ft_strcmp(toenv, "?="))
		fromenv = ft_itoa(shl.exit_code);
	else
		fromenv = word_from_env2(toenv);
	free(toenv);
	return (fromenv);
}

char	*add_fromenv(char *str, int k, int *j)
{
	char	*fromenv;
	char	*tmp;
	char	*res;

	res = NULL;
	fromenv = word_from_env(str, k, *j);
	tmp = ft_substr(str, 0, k - 1);
	if (fromenv)
	{
		res = ft_strjoin(tmp, fromenv);
		free(tmp);
		tmp = res;
		res = ft_strjoin(res, (char *)&str[*j]);
		free(fromenv);
	}
	else
		res = ft_strjoin(tmp, (char *)&str[*j]);
	*j = pointer(ft_strlen(tmp));
	free(tmp);
	free(str);
	return (res);
}

void	quot_correct(void)
{
	shl.t1 = shl.cells;
	while (shl.t1)
	{
		shl.i = 0;
		while (shl.t1->word[shl.i])
		{
			if (shl.t1->word[shl.i] == '$')
				shl.t1->word = dollar(shl.t1->word, &(shl.i), 0);
			else if (shl.t1->word[shl.i] == 34 || shl.t1->word[shl.i] == 39)
			{
				if (shl.t1->word[shl.i] == 34)
				{
					if (!dollar_check(shl.t1->word, shl.i))
						shl.t1->word = quot_del(shl.t1->word, &(shl.i), 34);
					else
						shl.t1->word = dollar(shl.t1->word, &(shl.i), 1);
				}
				else if (shl.t1->word[shl.i] == 39)
					shl.t1->word = quot_del(shl.t1->word, &(shl.i), 39);
			}
			shl.i++;
		}
		shl.t1 = shl.t1->next;
	}
}

// void	quot_correct(void)
// {
// 	shl.t1 = shl.cells;
// 	while (shl.t1)
// 	{
// 		shl.i = 0;
// 		while (shl.t1->word[shl.i])
// 		{
// 			printf("shl.t1->word[shl.i]1: %c\n", shl.t1->word[shl.i]);
// 			printf("shl.i1: %d\n", shl.i);
// 			if (shl.t1->word[shl.i] == '$')
// 				shl.t1->word = dollar(shl.t1->word, &(shl.i), 0);
// 			else if (shl.t1->word[shl.i] == 34 || shl.t1->word[shl.i] == 39)
// 			{
// 				if (shl.t1->word[shl.i] == 34)
// 				{
// 					if (!dollar_check(shl.t1->word, shl.i))
// 						shl.t1->word = quot_del(shl.t1->word, &(shl.i), 34);
// 					else
// 						shl.t1->word = dollar(shl.t1->word, &(shl.i), 1);
// 				}
// 				else if (shl.t1->word[shl.i] == 39) 
// 					shl.t1->word = quot_del(shl.t1->word, &(shl.i), 39);
// 			}
// 			printf("shl.t1->word2: %s\n", shl.t1->word);
// 			printf("strlen: %d\n", ft_strlen(shl.t1->word));
// 			printf("shl.t1->word[shl.i]2: %c\n", shl.t1->word[shl.i]);
// 			printf("shl.i2: %d\n\n", shl.i);
// 			shl.i++;
// 		}
// 		shl.t1 = shl.t1->next;
// 	}
// 	printf("shl.i232: %d\n\n", shl.i);
// }

