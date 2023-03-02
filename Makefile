NAME		=	minishell
MAN_FILES	=	main utils ft_simple_cmd ft_echo ft_export ft_cd
SRC_DIR		=	srcs/
OBJS_DIR	=	objs/
LIBFT_DIR	=	Libft/
LIBFT		=	libft.a
SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(MAN_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(MAN_FILES)))
GCC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RL			=	-lreadline
RM			=	rm -rf
FSAN		=	-fsanitize=address -g3

all:
	@mkdir -p $(OBJS_DIR)
	@make $(LIBFT_DIR)$(LIBFT)
	@make $(NAME)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@$(GCC) -c $< -o $@

$(NAME): $(OBJS)
	$(GCC) $(FSAN) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) $(RL) -o $(NAME)

$(LIBFT_DIR)$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS_DIR)

fclean:
	@make clean
	@$(RM) $(NAME)

re:
	@make fclean
	@make all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS)