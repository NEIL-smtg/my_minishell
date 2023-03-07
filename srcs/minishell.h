/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:22:17 by suchua            #+#    #+#             */
/*   Updated: 2023/03/08 01:28:50 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>

# define R2 1
# define R1 2
# define L2 3
# define L3 4

typedef struct s_shell
{
	char	*ms_prompt;
	char	**ms_env;
	char	*cmd_line;
	int		ms_status;
	int		add_history_req;
	int		fd[2];
	int		prev_fd;
}	t_shell;

//simple cmd
void	ft_pwd(t_shell *info, char **cmd);
void	ft_export(t_shell *info, char **cmd);
void	ft_env(t_shell *info, char **cmd);
void	ft_echo(t_shell *info, char **cmd);
void	ft_unset(t_shell *info, char **cmd);
void	ft_cd(t_shell *info, char **cmd);

//execve
int		cmd_exist(t_shell *info, char **cmd);
void	execute_cmd(t_shell *info);

//utils
void	ft_free2d(char **str);
void	error_msg(t_shell *info, char *cmd, char *error_arg);
void	free_everything(t_shell *info);
int		ft_isspace(char c);
void	swap_str(char **s1, char **s2);
int		get_2d_arr_size(char **s);
char	*get_cmd_path(char *cmd);
void	exit_the_program(char **cmds);
int		is_redir(char *cmd);

#endif