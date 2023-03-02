/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:13:23 by suchua            #+#    #+#             */
/*   Updated: 2023/03/01 20:11:23 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *src)
{
	char	*duplicate;
	int		i;

	duplicate = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	i = -1;
	while (src[++i])
		duplicate[i] = src[i];
	duplicate[i] = '\0';
	return (duplicate);
}

char	**ft_2d_strdup(char **src)
{
	int		row;
	char	**new;
	int		i;

	row = 0;
	while (src[row])
		++row;
	new = malloc(sizeof(char *) * (row + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < row)
		new[i] = ft_strdup(src[i]);
	new[i] = 0;
	return (new);
}
