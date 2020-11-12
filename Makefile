
NAME	=	minishell

HEADER	=	$(addprefix -I, $(lft)/printf $(lft)/gnl $(lft)/libft)

CFLAGS	=	-Wall -Werror -Wextra -g3 -fsanitize=address -fno-omit-frame-pointer 

CC		=	gcc

SRC	=	main.c \
		builtin/check_built_in.c\
		builtin/echo.c\
		builtin/export_support.c\
		builtin/export_unset.c\
		builtin/ft_cd.c\
		parsing/split_quote.c\
		support/alloc_n_erase.c\
		support/toolbox2.c\
		support/toolbox4.c\
		support/toolbox5.c\
		support/error.c\
		setup/prompt.c\
		setup/env_pwd.c\


OBJ = $(SRC:%.c=%.o)

%.o : %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(HEADER) -I.

$(NAME) : $(ft) $(OBJ)
	@make -C $(lft)
	@$(CC) -o $@  $^ $(CFLAGS) -L $(lft) -lftx
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