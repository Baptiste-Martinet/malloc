NAME	= libmy_malloc.so

CC	= gcc

RM	= rm -f

SRCS	= src/malloc.c \
			src/node_utils.c \
			src/best_fit.c \
			src/dump.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = 
CFLAGS += -Wall -Wextra -fPIC

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -shared

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re