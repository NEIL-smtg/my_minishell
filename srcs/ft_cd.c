/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:59:57 by suchua            #+#    #+#             */
/*   Updated: 2023/03/03 21:38:25 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char **env, char *var)
{
	int	i;

	i = 0;
	while (ft_strncmp(var, env[i], ft_strlen(var)))
		++i;
	return (ft_strdup(env[i] + ft_strlen(var)));
}

int	update_pwd(char *pwd, char *type, char **env)
{
	int		j;

	if (!ft_strncmp("..", type, 3))
	{
		
 	}
	else if (!ft_strncmp("~", type, 2))
	{
		free(pwd);
		pwd = get_var(env, "HOME=");
	}
	else
	{
		pwd = ft_strjoin_free(pwd, "/");
		pwd = ft_strjoin_free(pwd, type);
		if (access(pwd, F_OK))
			return (0);
	}
}

void	ft_cd(t_shell *info, char **cmd)
{
	int		i;
	char	*pwd;

	if (cmd[2])
	{
		error_msg(info, "cd", cmd[2]);
		return (0);
	}
	i = 0;
	pwd = get_var(info->ms_env, "PWD=");
	while (cmd[1][i])
	{
		while (cmd[1][i] && cmd[1][i] != '/')
			++i;
	}
}
