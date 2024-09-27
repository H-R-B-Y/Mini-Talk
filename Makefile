
CLI_DIR			= ./client_src
CLI_SRC			= ./client_src/main.c \
				./client_src/Makefile \
				./client_src/mini_client.h
CLI				= client

SRV_DIR			= ./server_src
SRV_SRC			= ./server_src/main.c \
				./server_src/general_functions.c\
				./server_src/handle_structs.c\
				./server_src/Makefile \
				./server_src/mini_server.h
SRV				= server

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a

TEST_DIR		= testing

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -O0


all:			Makefile $(SRV) $(CLI)

# Compile Server
$(SRV):			$(LIBFT) $(SRV_SRC)
		@\
		$(MAKE) --directory $(SRV_DIR)
		mv $(SRV_DIR)/$(SRV) $(SRV)


# Compile Client
$(CLI):			$(LIBFT) $(CLI_SRC)
		@\
		$(MAKE) --directory $(CLI_DIR)
		mv $(CLI_DIR)/$(CLI) $(CLI)


# Compile LIBFT dependency
$(LIBFT):
		@\
		$(MAKE) --directory $(LIBFT_DIR)

# Clean
clean:
		@\
		$(MAKE) --directory $(LIBFT_DIR) clean
		$(MAKE) --directory $(CLI_DIR) clean
		$(MAKE) --directory $(SRV_DIR) clean
		rm -f *.o

# Full Clean
fclean:			clean
		@\
		$(MAKE) --directory $(LIBFT_DIR) fclean
		$(MAKE) --directory $(CLI_DIR) fclean
		$(MAKE) --directory $(SRV_DIR) fclean
		rm -f server client || 0

# Relink
re:				fclean all

.phony: fclean clean re all 