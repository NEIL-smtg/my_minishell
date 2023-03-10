/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:41:12 by suchua            #+#    #+#             */
/*   Updated: 2023/03/14 19:11:12 by suchua           ###   ########.fr       */
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

void	close_infile_outfile(t_shell *info)
{
	if (info->infile != -1)
		close(info->infile);
	if (info->outfile != -1)
		close(info->outfile);
	info->infile = -1;
	info->outfile = -1;
}

void	close_all_pipe(t_shell *info, int n_pipe, int type)
{
	int	i;

	if (n_pipe < 1)
		return ;
	i = -1;
	close_infile_outfile(info);
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

int	need_to_fork(t_shell *info, char **cmd)
{
	char	**s;
	
	s = ft_split(cmd[0], 32);
	if (!ft_strncmp("exit", s[0], 5))
		exit(EXIT_SUCCESS);
	if (!ft_strncmp("cd", s[0], 3) && get_2d_arr_size(cmd) == 1)
	{
		ft_cd(info, s);
		ft_free2d(s);
		return (0);
	}
	ft_free2d(s);
	return (1);
}
