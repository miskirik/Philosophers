NAME = philo

SRCS=$(wildcard *.c)

CC = gcc
CFLAGS = -pthread -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS)
	@echo "Table is ready to eat"

clean:
	@rm -f $(NAME)
	@echo "Table is succesfuly cleaned"

re: clean all

.PHONY : all clean re
