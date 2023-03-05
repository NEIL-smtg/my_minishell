/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:55:59 by suchua            #+#    #+#             */
/*   Updated: 2023/03/05 01:58:21 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delimiter_exist(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	while (cmd[i])
	{
		if (ft_strncmp("<<", &cmd[i], 2))
			i += 2;
		else
			return (1);
		if (i >= len)
			break ;
	}
	return (0);
}
