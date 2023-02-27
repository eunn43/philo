NAME		= philo

CFLAGS		= -Wall -Wextra -Werror

INC_DIR		= ./

SRC_NAME	= philo
SRCS		= $(addsuffix .c, $(SRC_NAME))
OBJS		= $(addsuffix .o, $(SRC_NAME))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean :
	$(RM) $(OBJS)
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re