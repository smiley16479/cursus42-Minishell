
NAME	=	minishell

HEADER	=	$(addprefix -I, $(lft)/printf $(lft)/gnl $(lft)/libft)

CFLAGS	=	-Wall -Werror -Wextra 

SANITIZ	=	-g3 -fsanitize=address -fno-omit-frame-pointer 

CC		=	gcc

SRC	=	main.c \
		builtin/check_built_in.c\
		builtin/echo.c\
		builtin/export_support.c\
		builtin/ft_export.c\
		builtin/ft_unset.c\
		builtin/ft_cd.c\
		parsing/parsing_part1.c\
		parsing/parsing_part2.c\
		parsing/parsing_part3.c\
		parsing/parsing_part4.c\
		parsing/split_quote.c\
		parsing/split_redir.c\
		parsing/parse_exec.c\
		support/toolbox1.c\
		support/toolbox2.c\
		support/toolbox3.c\
		support/toolbox4.c\
		support/error.c\
		setup/prompt.c\
		setup/env_pwd.c\
		setup/signal.c\


OBJ = $(SRC:%.c=%.o)

%.o : %.c
	$(CC) -o $@ -c $< $(SANITIZ) $(CFLAGS) $(HEADER) -I.

$(NAME) : $(ft) $(OBJ)
	@make -C $(lft)
	@$(CC) -o $@  $^ $(SANITIZ) $(CFLAGS) -L $(lft) -lftx
	@echo minishell created 😁

lft	=	../../libft_extended

all : $(NAME)

libft:
	@make -C libft fclean
	@make -C libft

clean :
	make clean -C $(lft)
	rm -rf $(SRC:%.c=%.o)

fclean : clean
	@rm -f $(NAME)
	@make -C $(lft) fclean

re : fclean all

show:
		@echo "HEADER : " $(HEADER)

.PHONE : libft