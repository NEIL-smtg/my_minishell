/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:41:31 by suchua            #+#    #+#             */
/*   Updated: 2022/12/12 03:41:48 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FILE_D_SIZE
#  define FILE_D_SIZE 4864
# endif

char	*get_next_line(int fd);

//utils
char	*gnl_strjoin(char *line, char *partial);
int		ft_strlen_n(char *str);
void	ft_clean(char *partial);
int		ft_contain_n(char *str);

#endif