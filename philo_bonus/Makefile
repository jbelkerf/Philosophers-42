# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 16:30:24 by jbelkerf          #+#    #+#              #
#    Updated: 2025/05/17 15:39:01 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME=philo_bonus

CC=cc

SANITIZE_THREAD= -fsanitize=thread -g
SANITIZE_MEMORY= -fsanitize=address -g

CFLAGS=  -pthread 

HEADER= philo.h

MAN_SRC=  philo_bonus.c initial_data_bonus.c tools_bonus.c routine_bonus.c  start_simulation_bonus.c \
valid_argument_bonus.c free_resource_bonus.c monitor_bonus.c setter_getter_bonus.c stop_simulation_bonus.c

all: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) -o $(NAME)

m: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) $(SANITIZE_MEMORY) -o $(NAME)
	
t: $(MAN_SRC) $(HEADER)
	$(CC) $(CFLAGS) $(MAN_SRC) $(SANITIZE_THREAD) -o $(NAME)

clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)

re: fclean all