ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIB = libft.a

SYM_LINK = libft_malloc.so

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

INC_NAME = ft_malloc.h

SRC_NAME = free.c malloc.c utils.c realloc.c show_alloc_mem.c

OBJ_NAME = $(SRC_NAME:.c=.o)
INC = $(addprefix $(INC_PATH), $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

ifndef FLAG
	FLAG = -Wall -Werror -Wexta -lcurses
endif

.PHONY : all clean fclean re

all: $(LIB) $(NAME)

$(LIB):
	cd libft && $(MAKE)

$(NAME): $(OBJ_PATH) $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@ln -s $(NAME) $(SYM_LINK) 2> /dev/null || True
	@echo "$(NAME) created"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@echo "Directory ./obj created"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@gcc $(FLAGS) -Iincludes -o $@ -c $<
	@echo "Binary File done : $*$\"

clean:
	@rm -rf $(OBJ_PATH) 2> /dev/null
	@echo "Objs cleaned"

fclean: clean
	@rm -rf $(NAME) 2> /dev/null
	@rm -rf $(SYM_LINK) 2> /dev/null
	@echo "$(NAME) deleted"

re: fclean  all
