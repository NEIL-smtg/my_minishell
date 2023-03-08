/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:31:44 by suchua            #+#    #+#             */
/*   Updated: 2023/03/08 17:21:56 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_exist(char *str, char **env)
{
	int		i;
	char	*tmp;
	int		len;

	if (*str == 0)
		return (0);
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
	return (len + 1);
}

int	print_till_quote(char *s, t_shell *info, char quote)
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
		if (!ft_strncmp("$?", &s[i], 2))
		{
			ft_putnbr_fd(info->ms_status, 1);
			i += 2;
		}
		else if (s[i] == '$' && another == 39 && quote == 34)
			i += var_exist(&s[i + 1], info->ms_env);
		else
			write(1, &s[i++], 1);
	}
	return (i + 1);
}

static void	process_line(char *str, t_shell *info)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp("$?", &str[i], 2))
		{
			ft_putnbr_fd(info->ms_status, 1);
			i += 2;
		}
		else if (str[i] == 34 || str[i] == 39)
			i += print_till_quote(&str[i + 1], info, str[i]);
		else if (str[i] == '$')
			i += var_exist(&str[i + 1], info->ms_env);
		else
			write(1, &str[i++], 1);
	}
}

void	ft_echo(t_shell *info, char **cmd)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (cmd[++i])
	{
		if (i == 1 && !ft_strncmp("-n", cmd[i], 3))
		{
			flag = 1;
			continue ;
		}
		process_line(cmd[i], info);
		if (cmd[i + 1])
			write(1, " ", 1);
	}
	if (flag)
		write(1, "%%", 1);
	write(1, "\n", 1);
	info->ms_status = 0;
}
