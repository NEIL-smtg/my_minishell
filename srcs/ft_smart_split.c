/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smart_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:06:54 by suchua            #+#    #+#             */
/*   Updated: 2023/03/10 02:17:49 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_prev_valid(int i, char *str)
{
	int	j;
	int	within_single;
	int	within_double;

	if (i == 0)
		return (1);
	if (!str[i])
		return (0);
	j = 0;
	within_double = 0;
	within_single = 0;
	while (j < i)
	{
		if (str[j] == 34)
			within_single = !within_single;
		if (str[j] == 39)
			within_double = !within_double;
		++j;
	}
	if (within_single || within_double)
		return (1);
	return (0);
}

int	get_row(char *str)
{
	int	i;
	int	row;

	i = -1;
	row = 0;
	while (str[++i])
	{
		while (str[i] && str[i] != '|')
			++i;
		if (!check_prev_valid(i, str) || str[i] != '|')
			++row;
	}
	return (row + 1);
}

int	get_col(char *str, int curr_row)
{
	int	i;
	int	row;
	int	col;

	i = -1;
	col = 0;
	row = 0;
	while (str[++i])
	{
		while (str[i] && str[i] != '|')
		{
			++i;
			if (row == curr_row)
				col++;
		}
		if (!check_prev_valid(i, str) || str[i] != '|')
			++row;
		if (row == curr_row && i != 0)
			col++;
	}
	return (col + 1);
}

void	store_str(char *new, char *str, int curr_row)
{
	int	i;
	int	row;
	int	j;

	i = -1;
	j = 0;
	row = 0;
	while (str[++i])
	{
		while (str[i] && str[i] != '|')
		{
			if (row == curr_row)
				new[j++] = str[i];
			++i;
		}
		if (!check_prev_valid(i, str) || str[i] != '|')
			++row;
		if (row == curr_row && i != 0)
			new[j++] = str[i];
	}
	new[j] = 0;
}

char	**ft_smart_split(char *str)
{
	char	**new;
	int		i;

	new = ft_calloc(get_row(str), sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < get_row(str) - 1)
	{
		new[i] = ft_calloc(get_col(str, i), sizeof(char));
		store_str(new[i], str, i);
	}
	return (remove_space_quote(new));
}

// int main(void)
// {
// 	char str[100] = "echo \"dsaasd|dasdaa\" 12313";
// 	char **s = ft_smart_split(str);
// 	int i = -1;
// 	printf("row %d\n", get_row(str));
// 	while (s[++i])
// 		printf("%s\n", s[i]);
// 	exit(EXIT_SUCCESS);
// }