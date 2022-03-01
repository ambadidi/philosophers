# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 23:17:43 by abadidi           #+#    #+#              #
#    Updated: 2022/03/01 03:13:37 by abadidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRCS = philosophers.c utils.c utils_bis.c

FLAGS = -Wall -Wextra -Werror -c

FLAGPTHREAD = -lpthread

OBJS = $(SRCS:.c=.o)
OBJS2 = $(SRC2:.c=.o)

INC = philosophers.h

CC = gcc

all: $(NAME)

$(NAME): $(SRCS) $(INC)
	@$(CC) $(FLAGS) $(SRCS)
	@$(CC) $(OBJS) -o $(NAME) $(FLAGPTHREAD)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all 