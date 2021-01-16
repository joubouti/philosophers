NAME=philo_one

SRC=philo_one.c utils.c utils2.c

all: $(NAME)

CC=clang
FLAGS=-Wall -Werror -Wextra
$(NAME):
	@$(CC) $(FLAGS) $(SRC) -lpthread -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all