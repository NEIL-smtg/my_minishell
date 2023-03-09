/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:21:37 by suchua            #+#    #+#             */
/*   Updated: 2023/03/10 02:49:25 by suchua           ###   ########.fr       */
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
		info.input_line = readline(info.ms_prompt);
		if (!*(info.input_line))
		{
			free(info.input_line);
			continue ;
		}
		if (info.add_history_req)
			add_history(info.input_line);
		execute_cmd(&info);
		free(info.input_line);
	}
	return (0);
}
