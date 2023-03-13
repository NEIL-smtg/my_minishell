/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:55:41 by suchua            #+#    #+#             */
/*   Updated: 2023/03/14 04:34:23 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_cmd(char **cmd, t_shell *info)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(info, cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		ft_cd(info, cmd);
	else if (!ft_strncmp(cmd[0], "export", 7))
		ft_export(info, cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd(info, cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		ft_env(info, cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		ft_unset(info, cmd);
	else
		return (0);
	return (1);
}
