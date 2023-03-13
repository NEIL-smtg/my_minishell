/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:41:12 by suchua            #+#    #+#             */
/*   Updated: 2023/03/14 04:10:34 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd)
{
	int		i;
	char	*tmp;
	char	**path;

	i = -1;
	if (!access(cmd, F_OK))
		return (cmd);
	path = ft_split(getenv("PATH"), ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin_free(tmp, cmd);
		if (!access(tmp, F_OK))
		{
			ft_free2d(path);
			return (tmp);
		}
		free(tmp);
	}
	ft_free2d(path);
	return (NULL);
}

void	close_all_pipe(t_shell *info, int n_pipe, int type)
{
	int	i;

	if (n_pipe < 1)
		return ;
	i = -1;
	while (++i < n_pipe)
	{
		close(info->fd[i][1]);
		close(info->fd[i][0]);
		if (type == FREE_PIPE)
			free(info->fd[i]);
	}
	if (type == FREE_PIPE)
		free(info->fd);
}

void	init_pipe_fd(t_shell *info, int size)
{
	int	i;

	if (size < 2)
		return ;
	info->fd = ft_calloc((size - 1), sizeof(int *));
	i = -1;
	while (++i < size - 1)
	{
		info->fd[i] = ft_calloc(2, sizeof(int));
		if (pipe(info->fd[i]) == -1)
			ft_putendl_fd("Error piping !\n", 2);
	}
}
