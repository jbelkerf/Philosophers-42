# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 16:30:24 by jbelkerf          #+#    #+#              #
#    Updated: 2025/05/18 12:34:23 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME=philo

CC=cc

CFLAGS= -Wall -Wextra -Werror 

HEADER= philo.h

SRC=  philo.c initial_data.c tools.c routine.c stop_simulation.c start_simulation.c \
valid_argument.c free_resource.c monitor.c setter_getter.c

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