# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 21:32:36 by toshi             #+#    #+#              #
#    Updated: 2024/06/11 20:43:27 by tozeki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo

CC			:=	cc -fsanitize=thread -g
# CFLAGS		:=	-Wall -Wextra -Werror 

PTHREAD_FLAGS	:=	-lpthread

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

0:
	./$(NAME) 5 610 200 200 10
0+:
	./$(NAME) 5 610 200 200 100
0++:
	./$(NAME) 200 610 200 200 5
1:
	./$(NAME) 5 603 200 200 10
1+:
	./$(NAME) 5 602 200 200 100
1++:
	./$(NAME) 200 603 200 200 5
2:
	./$(NAME) 5 600 200 200 10
2+:
	./$(NAME) 5 600 200 200 100
2++:
	./$(NAME) 200 600 200 200 5
3:
	./$(NAME) 5 610 200 2 10
3+:
	./$(NAME) 5 610 200 2 100
3++:
	./$(NAME) 200 610 200 2 5
4:
	./$(NAME) 5 300 100 100 10
0-:
	./$(NAME) 5 600 600 600 5
1-:
	./$(NAME) 5 600 400 300 5
2-:
	./$(NAME) 5 6 4 3 5
3-:	
	./$(NAME) 5 603 201 200 10

.PHONY: all clean fclean re \
		0 1 1+ 1++ 2 2+ 2++ 3 3+ 3++ \
		0- 1- 2- 3-