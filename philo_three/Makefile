NAME=philo_three

SRC=philo_three.c utils.c utils2.c

all: $(NAME)

CC=clang
FLAGS=-Wall -Werror -Wextra
$(NAME):
	@$(CC) $(FLAGS) $(SRC) -lpthread -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all