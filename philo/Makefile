# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 16:30:24 by jbelkerf          #+#    #+#              #
#    Updated: 2025/04/19 17:49:45 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME=philo

CC=cc

SANITIZE_THREAD= -fsanitize=thread -g
SANITIZE_MEMORY= -fsanitize=address -g

CFLAGS=  -pthread 

HEADER= philo.h

MAN_SRC=  ft_atoi.c philo.c initial_data.c tools.c routine.c simulation.c

all: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) -o $(NAME)

m: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) $(SANITIZE_MEMORY) -o $(NAME)
	
t: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) $(SANITIZE_MEMORY) -o $(NAME)

clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)

re: fclean all