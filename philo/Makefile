# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 11:25:58 by jbelkerf          #+#    #+#              #
#    Updated: 2025/04/17 13:36:23 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

CC=cc

CFLAGS= -Wall -Wextra -Werror -pthread -fsanitize=address -g

HEADER= philo.h

MAN_SRC=  ft_atoi.c philo.c initial_data.c 

all: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) -o $(NAME)

clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)

re: fclean all