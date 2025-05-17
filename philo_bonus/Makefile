# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 16:30:24 by jbelkerf          #+#    #+#              #
#    Updated: 2025/05/17 15:52:55 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME=philo_bonus

CC=cc


CFLAGS= -Wall -Wextra -Werror -pthread 

HEADER= philo_bonus.h

SRC=  philo_bonus.c initial_data_bonus.c tools_bonus.c routine_bonus.c  start_simulation_bonus.c \
valid_argument_bonus.c free_resource_bonus.c monitor_bonus.c setter_getter_bonus.c stop_simulation_bonus.c

OBJ = $(SRC:.c=.o)

all:  $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c  $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all