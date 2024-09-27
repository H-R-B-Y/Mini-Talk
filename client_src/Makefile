
NAME			= client

HEADER			= mini_client.h

SRC				= 
OBJ				= $(SRC:.c=.o)

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -O0

LIBFT_DIR		= ../libft
LIBFT			= $(LIBFT_DIR)/libft.a

all:	$(NAME) $(HEADER) Makefile

$(NAME):		$(OBJ)
		@\
		$(CC) $(CFLAGS) main.c $(OBJ) $(LIBFT)  -o $(NAME)

.c.o:
		@\
		$(CC) $(CFLAGS) -c $<

clean:
		@\
		rm -f *.o

fclean: clean
		@\
		rm -f server

re: clean all

.phony: all re clean fclean