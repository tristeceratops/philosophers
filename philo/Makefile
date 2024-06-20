NAME := philo
FLAGS := -Wall -Wextra -Werror
FILES := main.c utils.c thread.c philo_meal.c
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