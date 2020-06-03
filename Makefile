# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shan <jdarko@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/06 12:11:03 by jdarko            #+#    #+#              #
#    Updated: 2020/05/07 18:12:32 by jdarko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
SYM_LINK = libft_malloc.so

LIBFT =  Libft/libft.a

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

INC_NAME = ft_malloc.h

SRC_NAME = free.c malloc.c utils.c realloc.c show_alloc_mem.c calloc.c

OBJ_NAME = $(SRC_NAME:.c=.o)
INC = $(addprefix $(INC_PATH), $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

ifndef FLAG
	FLAG = -Wall -Werror -Wextra 
endif

.PHONY : all clean fclean re

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJ_PATH) $(OBJ)
	@gcc $(FLAGS) -shared -o $(NAME) $(OBJ) $(LIBFT)
	@ln -s $(NAME) $(SYM_LINK) 2> /dev/null || True
	@echo "$(NAME) created"

$(LIBFT):
	echo "1"
	@make -C ./Libft

$(OBJ_PATH):
	echo "2"
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@echo "Directory ./obj created"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	echo "3"
	@gcc $(FLAGS) -fPIC  -I includes  -o $@ -c $< 
	@echo "Binary File done : $*$\"

clean:
	@rm -rf $(OBJ_PATH) 2> /dev/null
	@echo "Objs cleaned"
	@make clean -C ./Libft


fclean: clean
	@rm -rf $(NAME) 2> /dev/null
	@rm -rf $(SYM_LINK) 2> /dev/null
	@echo "$(NAME) deleted"
	@make fclean -C ./Libft


re: fclean  all
