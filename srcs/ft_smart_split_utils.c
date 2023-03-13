/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smart_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:24:12 by suchua            #+#    #+#             */
/*   Updated: 2023/03/14 04:33:50 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_quote(char *str)
{
	int	i;
	int	within_s;
	int	within_d;

	i = -1;
	within_s = 0;
	within_d = 0;
	while (str[++i])
	{
		if (str[i] == 39)
			within_d = !within_d;
		if (str[i] == 34)
			within_s = !within_s;
	}
	if (within_d || within_s)
		return (0);
	return (1);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = -1;
	j = 0;
	len = ft_strlen(str);
	new = ft_calloc((len + 1), sizeof(char));
	while (++i < len)
	{
		if (str[i] != 34 && str[i] != 39)
			new[j++] = str[i];
	}
	free(str);
	return (new);
}

char	*filter_quote(char *str)
{
	if (!ft_strncmp("echo ", str, 5))
		return (str);
	if (close_quote(str))
		return (remove_quote(str));
	return (str);
}

char	**remove_space(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i][j] == 32)
			++j;
		tmp = ft_strdup(&str[i][j]);
		free(str[i]);
		str[i] = tmp;
	}
	return (str);
}

char	**remove_space_quote(char **str, char sep)
{
	int		i;
	int		j;
	char	*tmp;

	if (sep == 32)
		return (remove_space(str));
	i = -1;
	while (str[++i])
	{
		j = 0;
		if (str[i + 1] && !ft_strncmp("|", str[i], 2)
			&& !ft_strncmp("| ", str[i + 1], 2))
		{
			free(str[i]);
			str[i] = ft_strdup("||");
			continue ;
		}
		while (str[i][j] && (str[i][j] == '|' || str[i][j] == 32))
			++j;
		tmp = ft_strdup(&str[i][j]);
		free(str[i]);
		str[i] = filter_quote(tmp);
	}
	return (str);
}
