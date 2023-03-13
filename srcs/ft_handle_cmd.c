/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:55:41 by suchua            #+#    #+#             */
/*   Updated: 2023/03/13 22:45:18 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_dup(t_shell *info, char *nxt_cmd, int index)
{
	if (nxt_cmd && index == 0)
		dup2(info->fd[index][1], 1);
	else if (!nxt_cmd)
		dup2(info->fd[index - 1][0], 0);
	else
	{
		dup2(info->fd[index - 1][0], 0);
		dup2(info->fd[index][1], 1);
	}
}

static void	child_exec(char **cmd, char **env)
{
	execve(get_cmd_path(cmd[0]), cmd, env);
	exit(EXIT_FAILURE);
}

void	parent_waiting(t_shell *info, pid_t child_id, char *s_cmd)
{
	waitpid(child_id, &info->ms_status, 0);
	if (info->ms_status)
	{
		ft_putstr_fd(s_cmd, 2);
		ft_putendl_fd(": Command not found", 2);
	}
}

void	iterate_pipe(t_shell *info, int n_pipe, char **s_cmd)
{
	int		i;
	pid_t	id;

	i = -1;
	while (s_cmd[++i])
	{
		id = fork();
		if (id == 0 && n_pipe > 0)
		{
			set_dup(info, s_cmd[i + 1], i);
			close_all_pipe(info, n_pipe);
		}
		if (id == 0)
			child_exec(ft_split(s_cmd[i], 32), info->ms_env);
		else
		{
			parent_waiting(info, id, s_cmd[i]);
			if (n_pipe > 0 && i < n_pipe)
				close(info->fd[i][1]);
		}
	}
}

void	ft_handle_cmd(t_shell *info)
{
	int		size;
	char	**s_cmd;

	s_cmd = ft_smart_split(info->input_line);
	size = get_2d_arr_size(s_cmd);
	init_pipe_fd(info, size);
	iterate_pipe(info, size - 1, s_cmd);
	close_all_pipe(info, size - 1);
}
