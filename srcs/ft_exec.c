/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:55:41 by suchua            #+#    #+#             */
/*   Updated: 2023/03/14 21:02:18 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_dup(t_shell *info, char *cmd, char *nxt_cmd, int index)
{
	if (nxt_cmd && index == 0)
	{
		if (info->infile != -1)
			dup2(info->infile, 0);
		if (info->outfile != -1)
		{
			dup2(info->outfile, 1);
			dup2(info->fd[index][1], info->outfile);
		}
		else
			dup2(info->fd[index][1], 1);
	}
	else if (!nxt_cmd)
	{
		if (info->infile != -1)
			dup2(info->infile, 0);
		else
			dup2(info->fd[index - 1][0], 0);
		if (info->outfile != -1)
			dup2(info->outfile, 1);
	}
	else
	{
		if (info->infile != -1)
		{
			dup2(info->infile, 0);
			dup2(info->fd[index][0], info->infile);
		}
		else
			dup2(info->fd[index - 1][0], 0);
		if (info->outfile != -1)
		{	
			dup2(info->outfile, 1);
			dup2(info->fd[index][1], info->outfile);
		}
		else
			dup2(info->fd[index][1], 1);
	}
}

static void	child_exec(char **cmd, t_shell *info, int npipe)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (is_redir(cmd[i]))
			cmd[i] = 0;
	if (npipe == 0)
	{
		if (info->infile != -1)
			dup2(info->infile, 0);
		if (info->outfile != -1)
			dup2(info->outfile, 1);
		close(info->infile);
		close(info->outfile);
		info->infile = -1;
		info->outfile = -1;
	}
	if (is_builtin_cmd(cmd, info))
		exit(EXIT_SUCCESS);
	execve(get_cmd_path(cmd[0]), cmd, info->ms_env);
	exit(EXIT_FAILURE);
}

int	parent_process(t_shell *info, pid_t child_id, char *s_cmd)
{
	waitpid(child_id, &info->ms_status, 0);
	close(info->infile);
	close(info->outfile);
	info->infile = -1;
	info->outfile = -1;
	if (info->ms_status)
	{
		ft_putstr_fd(s_cmd, 2);
		ft_putendl_fd(": Command not found", 2);
		return (0);
	}
	return (1);
}

void	iterate_pipe(t_shell *info, int n_pipe, char **s_cmd)
{
	int		i;
	pid_t	id;

	i = -1;
	while (s_cmd[++i])
	{
		id = fork();
		set_infile_outfile(info, s_cmd[i]);
		if (id == 0 && n_pipe > 0)
		{
			set_dup(info, s_cmd[i], s_cmd[i + 1], i);
			close_all_pipe(info, n_pipe, 0);
		}
		if (id == 0)
			child_exec(ft_split(s_cmd[i], 32), info, n_pipe);
		else
		{
			if (!parent_process(info, id, s_cmd[i]))
				break ;
			if (n_pipe > 0 && i < n_pipe)
				close(info->fd[i][1]);
		}
	}
}

void	ft_handle_cmd(t_shell *info)
{
	int		size;
	char	**s_cmd;

	s_cmd = ft_split(info->input_line, '|');
	if (!need_to_fork(info, s_cmd))
	{
		ft_free2d(s_cmd);
		return ;
	}
	size = get_2d_arr_size(s_cmd);
	init_pipe_fd(info, size);
	iterate_pipe(info, size - 1, s_cmd);
	close_all_pipe(info, size - 1, FREE_PIPE);
	ft_free2d(s_cmd);
}
