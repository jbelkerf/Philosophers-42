# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 11:25:58 by jbelkerf          #+#    #+#              #
#    Updated: 2025/04/14 12:06:37 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

CC=cc

CFLAGS= -Wall -Wextra -Werror -pthread

HEADER= philo.h

MAN_SRC=  ft_atoi.c philo.c 

all: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) -o $(NAME)

clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)

re: fclean all