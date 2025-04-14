# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 11:25:58 by jbelkerf          #+#    #+#              #
#    Updated: 2025/04/14 11:30:09 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

CC=cc

CFLAGS= -Wall -Wextra -Werror -pthread


MAN_SRC= philo.c philo.h

all: $(NAME) philo.h
	$(CC) $(CFLAGS) $(MAN_SRC) -o $(NAME)

clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)

re: fclean all