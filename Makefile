NAME=fillit

LIBFT_DIR=../libft_greg
SOURCES_FOLDER=srcs
HEADERS_FOLDER=includes
OBJ_FOLDER=out

CFLAGS=-Wall -Wextra -Werror -I $(LIBFT_DIR)/includes -I $(HEADERS_FOLDER)

SOURCES=$(SOURCES_FOLDER)/main.c \
		$(SOURCES_FOLDER)/load_map.c \
		$(SOURCES_FOLDER)/tools.c \
		$(SOURCES_FOLDER)/resolve.c
OUT=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SOURCES:.c=.o)))

all: preliminaire
	make $(NAME)

preliminaire:
	mkdir -p $(OBJ_FOLDER)
	make -C $(LIBFT_DIR)

$(NAME): $(OUT)
	gcc $(CFLAGS) -o $(NAME) $(LIBFT_DIR)/libft.a $(OUT)

$(OBJ_FOLDER)/%.o: $(SOURCES_FOLDER)/%.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: 
	make fclean
	make all
