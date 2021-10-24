# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 19:41:09 by sel-melc          #+#    #+#              #
#    Updated: 2019/11/18 15:58:03 by sel-melc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = nm_srcs/nm.c nm_srcs/utils.c
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

all : ft_nm

ft_nm : $(OBJ)
	make -C libft
	$(CC) -fsanitize=address -o ft_nm  $(NAME) $(OBJ)  libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) $? -o $@

clean : 
	rm -f $(OBJ) libft/*.o
fclean :
	rm -f $(OBJ) ft_nm libft/libft.a libft/*o

re : fclean all

.PHONY : clean fclean re all