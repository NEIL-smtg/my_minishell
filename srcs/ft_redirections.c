/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:54:41 by suchua            #+#    #+#             */
/*   Updated: 2023/03/09 19:45:43 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_right(t_shell *info, char **cmd, int i)
{
	info->fd[1] = open(cmd[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0000644);
	info->fd[0] = open(cmd[i + 1], O_RDONLY);
	if (!info->outfile)
	{
		error_msg(info, "open", "");
		exit(EXIT_FAILURE);
	}
	dup2(info->fd[1], 1);
	close(info->fd[1]);
	execve(get_cmd_path(cmd[0]), ft_2d_strndup(cmd, i), info->ms_env);
	error_msg(info, cmd[0], "Command not found.");
	exit(EXIT_FAILURE);
}

int	ft_contain_redir(t_shell *info, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp(">", cmd[i], 2))
			ft_redir_right(info, cmd, i);
		if (!ft_strncmp(">>", cmd[i], 3))
			return (1);
		if (!ft_strncmp("<", cmd[i], 2))
			return (1);
		if (!ft_strncmp("<<", cmd[i], 3))
			return (1);
	}
	return (0);
}
