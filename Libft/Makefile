# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 12:01:03 by suchua            #+#    #+#              #
#    Updated: 2023/01/10 19:16:09 by suchua           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC    	=    ft_mem/ft_memset.c \
	ft_str/ft_bzero.c \
	ft_mem/ft_memcpy.c \
	ft_mem/ft_memmove.c \
	ft_mem/ft_memchr.c \
	ft_mem/ft_memcmp.c \
	ft_str/ft_strlen.c \
	ft_is/ft_isalpha.c \
	ft_is/ft_isdigit.c \
	ft_is/ft_isalnum.c \
	ft_is/ft_isascii.c \
	ft_is/ft_isprint.c \
	ft_to/ft_toupper.c \
	ft_to/ft_tolower.c \
	ft_str/ft_strchr.c \
	ft_str/ft_strrchr.c \
	ft_str/ft_strncmp.c \
	ft_str/ft_strlcpy.c \
	ft_str/ft_strlcat.c \
	ft_str/ft_strnstr.c \
	ft_atoitoa/ft_atoi.c \
	ft_mem/ft_calloc.c \
	ft_str/ft_strdup.c \
	ft_str/ft_substr.c \
	ft_str/ft_strjoin.c \
	ft_str/ft_strtrim.c \
	ft_str/ft_split.c \
	ft_atoitoa/ft_itoa.c \
	ft_str/ft_strmapi.c \
	ft_put/ft_putchar_fd.c \
	ft_put/ft_putstr_fd.c \
	ft_put/ft_putendl_fd.c \
	ft_put/ft_putnbr_fd.c \
	ft_str/ft_striteri.c \
	ft_lst/ft_lstnew.c \
	ft_lst/ft_lstadd_front.c \
	ft_lst/ft_lstsize.c \
	ft_lst/ft_lstlast.c \
	ft_lst/ft_lstadd_back.c \
	ft_lst/ft_lstdelone.c \
	ft_lst/ft_lstclear.c \
	ft_lst/ft_lstiter.c \
	ft_lst/ft_lstmap.c	\
	get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c get_next_line/get_next_line_bonus.c \
	get_next_line/get_next_line_utils_bonus.c \
	ft_printf/ft_flags.c ft_printf/ft_print_ch.c ft_printf/ft_print_nb_utils.c ft_printf/ft_print_nb.c \
	ft_printf/ft_print_p_utils.c ft_printf/ft_print_p.c ft_printf/ft_print_usnb_utils.c \
	ft_printf/ft_print_usnb.c ft_printf/ft_print_x_utils.c ft_printf/ft_print_x.c \
	ft_printf/ft_printf.c

OBJS    	=    ${SRC:.c=.o}
NAME    	=    libft.a
CFLAGS  	=    -Wall -Wextra -Werror
GCC     	=    gcc

.c.o:
	@$(GCC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):    $(OBJS)
	@ar -crs $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJS)

fclean:    clean
	@rm -rf $(NAME)

re:
	@make fclean
	@make all
