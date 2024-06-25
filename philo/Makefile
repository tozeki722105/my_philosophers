# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 21:32:36 by toshi             #+#    #+#              #
#    Updated: 2024/06/25 19:50:14 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo

CC			:=	cc 
CFLAGS		:=	-Wall -Wextra -Werror -fsanitize=thread -g

SRCS		:=	initialize_common.c \
				initialize_forks.c \
				initialize_philos.c \
				initialize_threads_and_simulate.c \
				main.c \
				validate_args.c \
				simulate.c \
				simulate_utils.c \
				simulate_utils2.c \
				utils.c \
				utils2.c \
				utils_libft.c
OBJS		:=	$(patsubst %.c, %.o, $(SRCS))

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 