NAME 		= minishell

CC 			= cc
# CFLAGS 		= -Wall -Wextra -Werror
AR          = ar -rcs
RM          = rm -f
LIBS		= libft/libft.a
SRCS		= builtins/cd.c builtins/pwd.c builtins/echo.c builtins/builtins_error.c \
			builtins/export.c builtins/export2.c test_main.c
SRCS_BONUS  = 
OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(OBJS_BONUS)
else
	OBJECTS = $(OBJS)
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C libft all
	@$(CC) $(OBJECTS) libft/libft.a -o $(NAME)

bonus:
	@make WITH_BONUS=1 all

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:      
	$(RM) $(OBJS) $(OBJS_BONUS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	$(RM) libft/libft.a

re: 
	make fclean
	make all

.PHONY: all clean fclean re bonus

# eujeong

# CFLAGS = -Wall -Wextra -Werror
# NAME = minishell
# INCLUDES = includes
# #READLINE_LIB = -L${HOME}/.brew/opt/readline/lib
# #READLINE_INC = -I${HOME}/.brew/opt/readline/include
# READLINE_LIB = -L/opt/homebrew/opt/readline/lib
# READLINE_INC = -I/opt/homebrew/opt/readline/include
# SOURCES =   srcs/main.c\
#             srcs/lexer.c\
#             srcs/signal.c
# OBJECTS = $(SOURCES:.c=.o)

# all : $(NAME)

# $(NAME) : $(OBJECTS)
# 	make -C libft
# 	cc $^ -Llibft -lft $(READLINE_LIB) -lreadline -o $@

# %.o : %.c
# 	cc $(CFLAGS) -Ilibft/includes $(READLINE_INC) -I$(INCLUDES) -c $^ -o $@

# clean :
# 	make clean -C libft
# 	rm -f $(OBJECTS)

# fclean : clean
# 	make fclean -C libft
# 	rm -f $(NAME)

# re : fclean all

# .PHONY : all bonus clean fclean re
