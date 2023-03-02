/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:44:34 by suchua            #+#    #+#             */
/*   Updated: 2023/03/02 05:10:14 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_close_quote(char *str, int start)
{
	int	i;

	i = start;
	while (i >= 0)
	{
		--i;
	}
}

int	var_exist(char *var, char **env)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	while (var[i] >= 'A' && var[i] <= 'Z')
		++i;
	if (var[i] != 34 && var[i] != 39 && var[i])
		return (0);
	tmp = ft_strdup(var);
	tmp[i] = 0;
	len = i;
	i = 0;
	while (ft_strncmp(tmp, env[i], len))
		++i;
	free(tmp);
	if (!env[i])
		return (0);
	ft_putstr_fd(env[i] + len + 1, 1);
	return (1);
}

int	handle_word_by_word(char *str, char **env)
{
	int		i;

	i = 0;
	if (!check_close_quote(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && var_exist(&str[i + 1], env))
		{
			++i;
			while (str[i] && ft_isalpha(str[i]))
				++i;
		}
		else
			write(1, &str[i++], 1);
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
		if (!handle_word_by_word(cmd[i], info->ms_env))
		{
			ft_putendl_fd("Unclose quote", 2);
			return (0);
		}
		ft_putchar_fd(' ', 1);
	}
	if (!flag)
		write(1, "\n", 1);
	else
		write(1, "%%", 1);
}
