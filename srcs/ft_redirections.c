/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:54:41 by suchua            #+#    #+#             */
/*   Updated: 2023/03/08 02:19:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections(int is_redir, t_shell *info, char *cmd)
{
	char	**split_cmd;

	if (is_redir == -1)
		return ;
	split_cmd = ft_split(cmd, 32);

}

int	is_redir(char *cmd)
{
	char	**split_cmd;
	int		i;
	int		flag;

	split_cmd = ft_split(cmd, 32);
	i = -1;
	flag = -1;
	while (split_cmd[++i])
	{
		if (!ft_strncmp(">>", split_cmd[i], 3))
			flag = 1;
		if (!ft_strncmp(">", split_cmd[i], 2))
			flag = 2;
		if (!ft_strncmp("<<", split_cmd[i], 3))
			flag = 3;
		if (!ft_strncmp("<", split_cmd[i], 2))
			flag = 4;
		if (flag != -1)
			break ;
	}
	ft_free2d(split_cmd);
	return (flag);
}
