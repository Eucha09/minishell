CFLAGS = -Wall -Wextra -Werror
NAME = minishell
INCLUDES = includes
#READLINE_LIB = -L${HOME}/.brew/opt/readline/lib
#READLINE_INC = -I${HOME}/.brew/opt/readline/include
READLINE_LIB = -L/opt/homebrew/opt/readline/lib
READLINE_INC = -I/opt/homebrew/opt/readline/include
SOURCES =	srcs/main.c\
			srcs/lexer.c\
			srcs/signal.c
OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C Libft
	cc $^ -LLibft -lft $(READLINE_LIB) -lreadline -o $@

%.o : %.c
	cc $(CFLAGS) -ILibft/includes $(READLINE_INC) -I$(INCLUDES) -c $^ -o $@

clean :
	make clean -C Libft
	rm -f $(OBJECTS)

fclean : clean
	make fclean -C Libft
	rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re