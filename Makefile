# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 15:41:26 by lusehair          #+#    #+#              #
#    Updated: 2021/08/04 19:27:31 by lusehair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = srcs
HEADER_DIR = includes
OBJ_DIR = objs 

CC = gcc
CFLAGS += -Wall -Werror -Wextra -pthread
CFLAGS += -g3 -fsanitize=leak
#CFLAGS += -g3 
HEADER_FILE = $(HEADER_DIR)/philo.h \
			  $(HEADER_DIR)/structs.h

SRC_FILE = $(SRC_DIR)/init.c \
			$(SRC_DIR)/tools.c \
			$(SRC_DIR)/philo_life.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/libft.c \

OBJ = $(SRC_FILE:%.c=%.o)


$(NAME) :	$(OBJ) $(HEADER_FILE)
			$(CC) $(CFLAGS) -o $(NAME)  $(OBJ)  

all: $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
