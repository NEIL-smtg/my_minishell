/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:54:41 by suchua            #+#    #+#             */
/*   Updated: 2023/03/10 00:04:03 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//open(cmd[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0000644);
//open(cmd[i + 1], O_RDONLY);

void	ft_redir_right(t_shell *info, char **cmd, int i)
{
	pid_t	id;
	int		write_fd;
	int		read_fd;

	id = fork();
	write_fd = open(cmd[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0000644);
	read_fd = open(cmd[i + 1], O_RDONLY);
	if (id == 0)
	{
		dup2(write_fd, 1);
		close(write_fd);
		close(read_fd);
		execve(get_cmd_path(cmd[0]), ft_2d_strndup(cmd, i), info->ms_env);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(0, &info->ms_status, 0);
		if (info->ms_status != 0)
		{
			error_msg(info, cmd[0], "Command not found");
			exit(EXIT_FAILURE);
		}
	}
}

int	ft_contain_redir(t_shell *info, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp(">", cmd[i], 2))
		{
			ft_redir_right(info, cmd, i);
			return (1);
		}
		if (!ft_strncmp(">>", cmd[i], 3))
			return (1);
		if (!ft_strncmp("<", cmd[i], 2))
			return (1);
		if (!ft_strncmp("<<", cmd[i], 3))
			return (1);
	}
	return (0);
}
