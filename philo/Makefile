NAME = philo

SRCS=$(wildcard *.c)

CC = gcc
CFLAGS = -pthread -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS)
	@echo "\x1b[32m Table is ready to eat \x1b[0m"

clean:
	@rm -f $(NAME)
	@echo "\x1b[31m Table is succesfuly cleaned \x1b[0m"

fclean:clean

re: clean all

.PHONY : all clean fclean re
