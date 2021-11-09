NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I includes/

SRCD = srcs

SRC=	error_handle.c		\
		parse_utils.c		\
		philo.c				\
		status_handler.c

OBJ=$(SRC:%.c=%.o)

SRCS=$(addprefix srcs/, $(SRC))
OBJS=$(addprefix srcs/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(OBJD)/%.o: $(SRCD)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRCD)/*.o
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean