/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:33:34 by suchua            #+#    #+#             */
/*   Updated: 2023/01/05 19:30:26 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_split(char me, char c)
{
	return (me == c);
}

static int	get_row_num(char const *s, char c)
{
	int	row;

	row = 0;
	while (*s)
	{
		while (check_split(*s, c) && *s)
			s++;
		if (!check_split(*s, c) && *s)
			row++;
		while (!check_split(*s, c) && *s)
			s++;
	}
	return (row + 1);
}

static int	get_strlen(char const *s, char c, int cur_row)
{
	int	row;
	int	len;

	row = 0;
	len = 0;
	while (row < cur_row)
	{
		while (check_split(*s, c) && *s)
			s++;
		if (!check_split(*s, c) && *s)
			row++;
		while (!check_split(*s, c) && *s)
		{
			if (row == cur_row)
				len++;
			s++;
		}
	}
	return (len + 1);
}

static void	save_str(char *str, char const *s, char c, int cur_row)
{
	int	row;
	int	len;

	row = 0;
	len = 0;
	while (row < cur_row)
	{
		while (check_split(*s, c) && *s)
			s++;
		if (!check_split(*s, c) && *s)
			row++;
		while (!check_split(*s, c) && *s)
		{
			if (row == cur_row)
				str[len++] = *s;
			s++;
		}
		str[len] = '\0';
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**new_arr;

	if (!s)
		return (NULL);
	i = 0;
	new_arr = (char **) malloc (get_row_num(s, c) * sizeof(char *));
	while (i < get_row_num(s, c) - 1)
	{
		new_arr[i] = (char *) ft_calloc(get_strlen(s, c, (i + 1)),
				sizeof(char));
		save_str(new_arr[i], s, c, (i + 1));
		i++;
	}
	new_arr[i] = 0;
	return (new_arr);
}

// int main(void)
// {
// 	char const str[] = "      split       this for   me  !       ";
// 	char c = (char)' ';
// 	char **p = ft_split(str, c);
// 	int i = 0;

// 	while (i < get_row_num(str, c))
// 	{
// 		printf("%s\n", p[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < get_row_num(str, c) - 1)
// 	{
// 		free(p[i]);
// 		i++;
// 	}
// 	return (0);
// }