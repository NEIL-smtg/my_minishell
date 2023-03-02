/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:21:37 by suchua            #+#    #+#             */
/*   Updated: 2023/03/02 23:01:30 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_shell *info, char **env)
{
	char	*user;
	char	*ms;

	user = getenv("USER");
	ms = "@minishell->";
	info->ms_prompt = ft_strjoin(user, ms);
	info->ms_env = ft_2d_strdup(env);
}

void	process_line(t_shell *info)
{
	char	**cmd_line;

	info->ms_status = 0;
	cmd_line = ft_split(info->cmd_line, 32);
	if (!ft_strncmp("echo", cmd_line[0], 5))
		ft_echo(info, cmd_line);
	else if (!ft_strncmp("cd", cmd_line[0], 3))
		ft_cd(info, cmd_line);
	else if (!ft_strncmp("pwd", cmd_line[0], 4))
		ft_pwd(info, cmd_line);
	else if (!ft_strncmp("export", cmd_line[0], 7))
		ft_export(info, cmd_line);
	else if (!ft_strncmp("unset", cmd_line[0], 6))
		ft_unset(info, cmd_line);
	else if (!ft_strncmp("env", cmd_line[0], 4))
		ft_env(info, cmd_line);
	else if (!ft_strncmp("exit", cmd_line[0], 5))
		exit(EXIT_SUCCESS);
	else
	{
		info->ms_status = 127;
		printf("%s : Command not found !\n", cmd_line[0]);
	}
	ft_free2d(cmd_line);
}

int	main(int ac, char **av, char **env)
{
	t_shell	info;

	init(&info, env);
	while (1)
	{
		info.cmd_line = readline(info.ms_prompt);
		if (!*(info.cmd_line))
		{
			free(info.cmd_line);
			continue ;
		}
		add_history(info.cmd_line);
		process_line(&info);
		free(info.cmd_line);
	}
	free_everything(&info);
	return (0);
}
