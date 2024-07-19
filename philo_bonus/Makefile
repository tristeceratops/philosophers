NAME := philo
FLAGS := -Wall -Wextra -Werror -g -oFast
FILES := main.c utils.c thread.c utils2.c ft_exit.c
OBJ := $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) -L$(LIBFT) -lft -o $@

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all