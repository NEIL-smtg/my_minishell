/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:34:38 by suchua            #+#    #+#             */
/*   Updated: 2023/03/10 02:49:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

void	ft_free2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	error_msg(t_shell *info, char *cmd, char *error_arg)
{
	char	*str;

	info->ms_status = 127;
	str = ": No such file or directory\n";
	write(STDOUT_FILENO, cmd, ft_strlen(cmd));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, error_arg, ft_strlen(error_arg));
	write(STDOUT_FILENO, str, ft_strlen(str));
}

void	free_everything(t_shell *info)
{
	free(info->input_line);
	ft_free2d(info->ms_env);
	free(info->ms_prompt);
}

void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
