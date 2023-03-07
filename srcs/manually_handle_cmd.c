/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manually_handle_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:50:10 by suchua            #+#    #+#             */
/*   Updated: 2023/03/08 01:44:44 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd)
{
	int		i;
	char	*tmp;
	char	**path;

	i = -1;
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

static int	self_implement(t_shell *info, char **cmd_line)
{
	int	flag;

	flag = 0;
	if (!ft_strncmp("echo", cmd_line[0], 5))
		ft_echo(info, cmd_line);
	else if (!ft_strncmp("cd", cmd_line[0], 3))
		ft_cd(info, cmd_line);
	if (!ft_strncmp("pwd", cmd_line[0], 4))
		ft_pwd(info, cmd_line);
	else if (!ft_strncmp("export", cmd_line[0], 7))
		ft_export(info, cmd_line);
	else if (!ft_strncmp("unset", cmd_line[0], 6))
		ft_unset(info, cmd_line);
	else if (!ft_strncmp("env", cmd_line[0], 4))
		ft_env(info, cmd_line);
	else
		flag = 1;
	ft_free2d(cmd_line);
	if (flag)
		return (0);
	return (1);
}

void	child_exec(t_shell *info, char **cmds)
{
	char	**s_cmd;
	char	*cmd_path;

	redirections(is_redir(cmds[0]), info, cmds[0]);
	if (info->prev_fd != -1)
	{
		dup2(info->prev_fd, 0);
		close(info->prev_fd);
	}
	if (cmds[1])
		dup2(info->fd[1], 1);
	close(info->fd[0]);
	close(info->fd[1]);
	if (!self_implement(info, ft_split(cmds[0], 32)))
	{
		s_cmd = ft_split(cmds[0], 32);
		cmd_path = get_cmd_path(s_cmd[0]);
		execve(cmd_path, s_cmd, info->ms_env);
		free(cmd_path);
		ft_free2d(s_cmd);
	}
	else
		exit(EXIT_SUCCESS);
}

void	execute_cmd(t_shell *info)
{
	int		i;
	char	**cmds;
	pid_t	id;

	i = -1;
	info->prev_fd = -1;
	cmds = ft_split(info->cmd_line, '|');
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
