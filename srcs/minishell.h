/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:22:17 by suchua            #+#    #+#             */
/*   Updated: 2023/03/14 04:05:05 by suchua           ###   ########.fr       */
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
# define FREE_PIPE 1

//main data struct
typedef struct s_shell
{
	char	*ms_prompt;
	char	**ms_env;
	char	*input_line;
	int		ms_status;
	int		add_history_req;
	int		**fd;
	int		infile;
	int		outfile;
}	t_shell;

//built-in cmd
void	ft_pwd(t_shell *info, char **cmd);
void	ft_export(t_shell *info, char **cmd);
void	ft_env(t_shell *info, char **cmd);
void	ft_echo(t_shell *info, char **cmd);
void	ft_unset(t_shell *info, char **cmd);
void	ft_cd(t_shell *info, char **cmd);

//built in checker for execve
int		is_builtin_cmd(char **cmd, t_shell *info);

//redirection
int		ft_contain_redir(t_shell *info, char **cmd);

//execve
void	ft_handle_cmd(t_shell *info);

//execve utils
void	close_all_pipe(t_shell *info, int n_pipe, int type);
void	init_pipe_fd(t_shell *info, int size);
char	*get_cmd_path(char *cmd);

//utils
void	ft_free2d(char **str);
void	error_msg(t_shell *info, char *cmd, char *error_arg);
void	free_everything(t_shell *info);
int		ft_isspace(char c);
void	swap_str(char **s1, char **s2);
int		get_2d_arr_size(char **s);

//smart split for pipe
char	**ft_smart_split(char *str, char sep);
char	**remove_space_quote(char **str, char sep);

#endif