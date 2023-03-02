/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:31:44 by suchua            #+#    #+#             */
/*   Updated: 2023/03/02 17:56:49 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_exist(char *str, char **env)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	while (str[i] >= 'A' && str[i] <= 'Z')
		++i;
	tmp = ft_strdup(str);
	tmp[i] = 0;
	len = ft_strlen(tmp);
	i = 0;
	while (ft_strncmp(tmp, env[i], len))
		++i;
	free(tmp);
	if (!env[i])
		return (0);
	ft_putstr_fd(env[i] + len + 1, 1);
	return (len);
}

int	print_till_quote(char *s, char **env, char quote)
{
	int		i;
	char	another;

	i = 0;
	if (quote == 34)
		another = 39;
	else
		another = 34;
	while (s[i] && s[i] != quote)
	{
		if (s[i] == '$' && another == 39 && quote == 34)
			i += var_exist(&s[i + 1], env);
		else
			write(1, &s[i], 1);
		++i;
	}
	return (i + 1);
}

static void	process_line(char *str, char **env)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			i += print_till_quote(&str[i + 1], env, str[i]);
		else if (str[i] == '$')
			i += var_exist(&str[i + 1], env);
		else
			write(1, &str[i], 1);
	}
}

void	ft_echo(t_shell *info, char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (cmd[++i])
	{
		if (i == 1 && !ft_strncmp("-n", cmd[i], 3))
		{
			flag = 1;
			continue ;
		}
		process_line(cmd[i], info->ms_env);
		if (cmd[i + 1])
			write(1, " ", 1);
	}
	if (flag)
		write(1, "%%", 1);
	write(1, "\n", 1);
}
