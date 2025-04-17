# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 16:30:24 by jbelkerf          #+#    #+#              #
#    Updated: 2025/04/17 16:30:25 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME=philo

CC=cc

SANITIZE=-fsanitize=address -g

CFLAGS= -Wall -Wextra -Werror -pthread 

HEADER= philo.h

MAN_SRC=  ft_atoi.c philo.c initial_data.c fork.c

all: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) -o $(NAME)

sani: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) $(SANITIZE) -o $(NAME)

clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)

re: fclean all