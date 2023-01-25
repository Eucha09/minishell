NAME 		= minishell

CC 			= cc
# CFLAGS 		= -Wall -Wextra -Werror
AR          = ar -rcs
RM          = rm -f
LIBS		= libft/libft.a
SRCS		= cd.c test_main.c
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