/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manually_handle_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:50:10 by suchua            #+#    #+#             */
/*   Updated: 2023/03/10 03:03:59 by suchua           ###   ########.fr       */
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

static int	self_implement(t_shell *info, char **s_cmd)
{
	int	flag;

	flag = 1;		
	if (!ft_strncmp("echo ", s_cmd[0], 5))
		ft_echo(info, s_cmd);
	else if (!ft_strncmp("cd ", s_cmd[0], 3))
		ft_cd(info, s_cmd);
	else if (!ft_strncmp("pwd ", s_cmd[0], 4))
		ft_pwd(info, s_cmd);
	else if (!ft_strncmp("export ", s_cmd[0], 7))
		ft_export(info, s_cmd);
	else if (!ft_strncmp("unset ", s_cmd[0], 6))
		ft_unset(info, s_cmd);
	else if (!ft_strncmp("env ", s_cmd[0], 4))
		ft_env(info, s_cmd);
	else if (!ft_contain_redir(info, s_cmd))
		flag = 0;
	else
		flag = 0;
	ft_free2d(s_cmd);
	return (flag);
}

void	child_exec(t_shell *info, char **cmds)
{
	char	**s_cmd;
	char	*cmd_path;
	char	*nxt_cmd;

	nxt_cmd = cmds[1];
	if (info->prev_fd != -1)
	{
		dup2(info->prev_fd, 0);
		close(info->prev_fd);
	}
	if (nxt_cmd)
		dup2(info->fd[1], 1);
	close(info->fd[0]);
	close(info->fd[1]);
	if (self_implement(info, ft_split(cmds[0], 32)))
		exit(EXIT_SUCCESS);
	s_cmd = ft_split(cmds[0], 32);
	cmd_path = get_cmd_path(s_cmd[0]);
	execve(cmd_path, s_cmd, info->ms_env);
	error_msg(info, s_cmd[0], "Command not found");
	exit(EXIT_FAILURE);
}

void	execute_cmd(t_shell *info)
{
	int		i;
	char	**cmds;
	pid_t	id;

	i = -1;
	info->prev_fd = -1;
	cmds = ft_smart_split(info->input_line);
	if (!ft_strncmp(cmds[0], "exit", 5))
		exit_the_program(cmds);
	while (++i < get_2d_arr_size(cmds))
	{
		if (pipe(info->fd) == -1)
			return ;
		id = fork();
		if (id == 0)
			child_exec(info, &cmds[i]);
		info->prev_fd = info->fd[0];
		close(info->fd[1]);
	}
	i = -1;
	while (++i < get_2d_arr_size(cmds))
		waitpid(0, &info->ms_status, 0);
	ft_free2d(cmds);
}
