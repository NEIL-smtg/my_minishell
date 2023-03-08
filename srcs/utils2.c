/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:55:59 by suchua            #+#    #+#             */
/*   Updated: 2023/03/08 19:31:49 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_2d_arr_size(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	exit_the_program(char **cmds)
{
	ft_free2d(cmds);
	exit(EXIT_SUCCESS);
}

int	is_quote(char c)
{
	return (c == 34 || c == 39);
}


// +1 to skip current quote char
int	store_till_quote(char q, char *line, int *i, char *new)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != q)
	{
		new[j] = line[j];
		++j;
	}
	(*i) += j + 1;
	return (j);
}

void	filter_cmd_line(t_shell *info)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	new = malloc(sizeof(char) * (ft_strlen(info->cmd_line) + 1));
	*new = 0;
	i = 0;
	j = 0;
	while (info->cmd_line[i])
	{
		while (info->cmd_line[i] && !is_quote(info->cmd_line[i]))
			new[j++] = info->cmd_line[i++];
		if (info->cmd_line[i] == 34)
			j += store_till_quote(34, &info->cmd_line[i + 1], &i, &new[j]);
		else if (info->cmd_line[i] == 39)
			j += store_till_quote(39, &info->cmd_line[i + 1], &i, &new[j]);
		else
			new[j++] = info->cmd_line[i];
		++i;
	}
	new[j] = 0;
	free(info->cmd_line);
	info->cmd_line = new;
}
