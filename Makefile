LIBFT = libft/libft.a
LDFLAGS = -L libft -lft -lm
NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -O3 -Ilibft -Iinc
SRC = src/main.c \
	  src/raycaster.c \
	  src/draw.c \
	  src/hooks.c \
	  src/parser.c \
	  src/textures.c \
	  src/utils.c	\
	  src/parser_aux.c \
	  src/hooks_aux.c	\
	  src/parser_aux2.c	\
	  src/parser_aux3.c
OBJ = $(SRC:.c=.o)
RM=/bin/rm -f
UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
	# mac
    CC = gcc
    CFLAGS += -D MAC_OS -Iminilibx_macos
    LDFLAGS += -framework OpenGL -framework AppKit -L minilibx_macos -lmlx 
    MINILIBX = minilibx_macos/libmlx.a
    MINILIB_PATH = ./minilibx_macos
else
	#Linux and others...
    CC	= gcc
    LDFLAGS += -lbsd -L minilibx-linux -lmlx -lXext -lX11
    CFLAGS += -Iminilibx-linux
    MINILIBX = minilibx-linux/libmlx.a
    MINILIB_PATH = ./minilibx-linux
endif

all: $(NAME)

$(LIBFT):
	@echo Compiling libft...
	@make bonus -sC ./libft
	@echo libft done!

$(MINILIBX):
	@echo Compiling minilibx...
	@make -sC $(MINILIB_PATH)
	@echo minilibx done!
	
$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MINILIBX) $(LDFLAGS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make clean -C ./libft
	@make clean -C ./$(MINILIB_PATH)
	$(RM) $(OBJ)
	$(RM) $(OBJBONUS)

fclean: clean
	@make fclean -C ./libft
	@make clean -sC ./$(MINILIB_PATH)
	$(RM) $(NAME)

re:: fclean
re:: all

asan:: CFLAGS += -fsanitize=address -g3
asan:: LDFLAGS += -fsanitize=address
asan:: re


normi:
	@norminette src inc libft

.PHONY: all clean fclean re normi
