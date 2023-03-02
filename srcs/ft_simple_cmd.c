/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:36:55 by suchua            #+#    #+#             */
/*   Updated: 2023/03/02 01:10:03 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	process_env(char **dup_env, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = size;
		while (--j > i)
			if (ft_strncmp(dup_env[i], dup_env[j], ft_strlen(dup_env[i])) > 0)
				swap_str(&dup_env[i], &dup_env[j]);
	}
}

void	ft_export(t_shell *info, char **cmd)
{
	char	**dup_env;
	int		i;
	int		j;
	int		size;

	if (cmd[1])
	{
		error_msg(info, "export", cmd[1]);
		return ;
	}
	dup_env = ft_2d_strdup(info->ms_env);
	size = 0;
	while (dup_env[size])
		++size;
	process_env(dup_env, size);
	i = -1;
	while (++i < size)
		ft_putendl_fd(dup_env[i], 1);
	ft_free2d(dup_env);
}

void	ft_pwd(t_shell *info, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		error_msg(info, "pwd", cmd[1]);
		return ;
	}
	i = 0;
	while (ft_strncmp("PWD=", info->ms_env[i], 4))
		++i;
	ft_putendl_fd(info->ms_env[i] + 4, 1);
}

void	ft_env(t_shell *info, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		error_msg(info, "env", cmd[1]);
		return ;
	}
	i = -1;
	while (info->ms_env[++i])
		ft_putendl_fd(info->ms_env[i], 1);
}
