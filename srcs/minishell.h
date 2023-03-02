/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:22:17 by suchua            #+#    #+#             */
/*   Updated: 2023/03/02 02:17:19 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PRINT 1

typedef struct s_shell
{
	char	*ms_prompt;
	char	**ms_env;
	char	*cmd_line;
	int		ms_status;
}	t_shell;

//simple cmd
void	ft_pwd(t_shell *info, char **cmd);
void	ft_export(t_shell *info, char **cmd);
void	ft_env(t_shell *info, char **cmd);
void	ft_echo(t_shell *info, char **cmd);

//utils
void	ft_free2d(char **str);
void	error_msg(t_shell *info, char *cmd, char *error_arg);
void	free_everything(t_shell *info);
int		ft_isspace(char c);

#endif
