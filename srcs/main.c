/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:21:37 by suchua            #+#    #+#             */
/*   Updated: 2023/03/08 00:06:48 by suchua           ###   ########.fr       */
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
	info->ms_status = 0;
}

int	main(int ac, char **av, char **env)
{
	t_shell	info;

	init(&info, env);
	while (1)
	{
		info.add_history_req = 1;
		info.cmd_line = readline(info.ms_prompt);
		if (!*(info.cmd_line))
		{
			free(info.cmd_line);
			continue ;
		}
		execute_cmd(&info);
		if (info.add_history_req)
			add_history(info.cmd_line);
		free(info.cmd_line);
	}
	free_everything(&info);
	return (0);
}
