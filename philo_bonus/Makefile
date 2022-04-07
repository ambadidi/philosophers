# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 23:17:43 by abadidi           #+#    #+#              #
#    Updated: 2022/04/06 23:20:22 by abadidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = philosophers.c philosophers_help.c utils.c utils_bis.c utils_tiers.c check_if_digit.c ft_itoa.c

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