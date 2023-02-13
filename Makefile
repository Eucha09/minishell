# CFLAGS = -Wall -Wextra -Werror
NAME = minishell
INCLUDES = includes
READLINE_LIB = -L${HOME}/.brew/opt/readline/lib
READLINE_INC = -I${HOME}/.brew/opt/readline/include
# READLINE_LIB = -L/opt/homebrew/opt/readline/lib
# READLINE_INC = -I/opt/homebrew/opt/readline/include
SOURCES =   srcs/main.c\
            srcs/lexer.c\
			srcs/astree.c\
			srcs/parser/parser.c\
			srcs/parser/cmdline.c\
			srcs/parser/cmd.c\
			srcs/parser/simple_cmd.c\
			srcs/parser/cmd_prefix.c\
			srcs/parser/cmd_suffix.c\
			srcs/parser/io_redirect.c\
			srcs/execute.c\
			srcs/command.c\
            srcs/signal.c\
			srcs/utils.c\
			srcs/here_doc.c\
			srcs/builtins/builtins_error.c\
			srcs/builtins/cd.c\
			srcs/builtins/echo.c\
			srcs/builtins/env.c\
			srcs/builtins/export.c\
			srcs/builtins/export2.c\
			srcs/builtins/pwd.c\
			srcs/builtins/unset.c\
			srcs/builtins/ft_exit.c\
			srcs/path.c\
			srcs/execve.c


OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C libft
	cc $^ -Llibft -lft $(READLINE_LIB) -lreadline -o $@

%.o : %.c
	cc $(CFLAGS) -Ilibft/includes $(READLINE_INC) -I$(INCLUDES) -c $^ -o $@

clean :
	make clean -C libft
	rm -f $(OBJECTS)

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
