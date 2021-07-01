# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igor <igor@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 05:51:11 by igor              #+#    #+#              #
#    Updated: 2021/07/01 06:47:01 by igor             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = includes/philo.h

SRC_PATH = srcs

SRCS    =		main.c			\
				philosophers.c	\
				init_struct.c	\
				print.c			\
				utils.c			\
				utils2.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(INCLUDES) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@printf "\r\033[48;5;15;30m✅ $(NAME)\033[0m\033[K\n"
			
clean :
			@rm -f $(OBJS)

fclean :	clean
			@rm -f $(NAME)

re: fclean all