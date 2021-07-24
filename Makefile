NAME := server

CC := clang
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak -fsanitize=signed-integer-overflow -c
LFLAGS := -Wall -Werror -Wextra -fsanitize=address -fsanitize=leak -fsanitize=signed-integer-overflow -o
SRC_DIR := ./src/
OBJ_DIR := ./obj/

SRC_FILES := main.c \
			 queue.c

HEADER := -I includes/

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

RM := rm -f

all: obj $(NAME)

obj: $(SRCS)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@ $(HEADER)

$(NAME): $(OBJS)
	$(CC) $(LFLAGS) $(NAME) $(OBJS) $(HEADER)

clean:
	$(RM) $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all obj clean fclean re