NAME = philo
SRCS = philo.c utils.c error_utils.c simulation_utils.c simulation_handler.c

OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[33m        _     _ _       \033[0m"
	@echo "\033[33m       | |   (_) |      \033[0m"
	@echo "\033[33m  _ __ | |__  _| | ___  \033[0m"
	@echo "\033[33m | '_ \| '_ \| | |/ _ \ \033[0m"
	@echo "\033[34m | |_) | | | | | | (_) |\033[0m"
	@echo "\033[34m | .__/|_| |_|_|_|\___/ \033[0m"
	@echo "\033[34m | |                     \033[0m"
	@echo "\033[34m |_|                     \033[0m"
	@echo "Simulation is ready!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "Object files removed!"

fclean: clean
	@rm -rf $(NAME)
	@echo "Program is removed!"
re: fclean all

.PHONY: all clean fclean re
