/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manually_handle_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:50:10 by suchua            #+#    #+#             */
/*   Updated: 2023/03/06 02:08:56 by suchua           ###   ########.fr       */
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

int		cmd_exist(t_shell *info, char **cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd[0]);
	if (!cmd_path)
		return (0);
	free(cmd_path);
	return (1);
}


void	execute_cmd(t_shell *info, char **cmd)
{
	char	*cmd_path;
	pid_t	id;

	cmd_path = get_cmd_path(cmd[0]);
	id = fork();
	if (id == -1)
		return ;
	if (id == 0)
		execve(cmd_path, cmd, info->ms_env);
	else
		waitpid(0, &info->ms_status, 0);
	free(cmd_path);
}
