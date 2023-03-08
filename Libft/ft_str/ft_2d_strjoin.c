/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:01:22 by suchua            #+#    #+#             */
/*   Updated: 2023/03/08 18:04:48 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_strs_len(char **s, int size, char *sep)
{
	int	i;
	int	n;

	n = 0;
	i = -1;
	while (++i < size)
		n += ft_strlen(s[i]);
	n += (size - 1) * len(sep) + 1;
	return (n);
}

void	concat(char *tab, char *sep)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
		i++;
	j = 0;
	while (sep[j])
	{
		tab[i + j] = sep[j];
		j++;
	}
	tab[i + j] = '\0';
}

char	*ft_2d_strjoin(int size, char **strs, char *sep)
{
	char	*tab;
	int		i;

	if (size == 0)
		return ((char *)malloc(sizeof(char)));
	tab = (char *)malloc(get_strs_len(strs, size, sep) * sizeof(char));
	if (!tab)
		return (NULL);
	tab[0] = '\0';
	i = -1;
	while (++i < size)
	{
		concat(tab, strs[i]);
		if (i != size - 1)
			concat(tab, sep);
	}
	return (tab);
}
