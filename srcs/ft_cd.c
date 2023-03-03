/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:59:57 by suchua            #+#    #+#             */
/*   Updated: 2023/03/03 22:14:42 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *info, char **cmd)
{
	int		i;
	char	new_pwd[4096];

	if (cmd[2])
	{
		error_msg(info, "cd", cmd[2]);
		return ;
	}
	if (chdir(cmd[1]) == -1)
	{
		error_msg(info, "cd", cmd[1]);
		return ;
	}
	getcwd(new_pwd, sizeof(new_pwd));
	i = 0;
	while (ft_strncmp("PWD=", info->ms_env[i], 4))
		++i;
	free(info->ms_env[i]);
	info->ms_env[i] = ft_strdup("PWD=");
	info->ms_env[i] = ft_strjoin_free(info->ms_env[i], new_pwd);
}
