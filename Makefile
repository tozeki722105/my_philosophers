# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 21:32:36 by toshi             #+#    #+#              #
#    Updated: 2024/05/17 02:24:38 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo
CC			:=	cc 
# CFLAGS		:=	-Wall -Wextra -Werror 
PTHREAD_FLAGS	:=	-lpthread
SRC_PATHS	:=	./
SRCS		:=	$(foreach path, $(SRC_PATHS), $(wildcard $(path)*.c))
OUT_PATTERN	:=	tmp.c make_last_eat_id_array.c
OBJS		:=	$(patsubst %.c, %.o, $(filter-out $(OUT_PATTERN), $(SRCS)))

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
0*:
	./$(NAME) 200 610 200 200 3
1:
	./$(NAME) 5 601 200 200 10
1+:
	./$(NAME) 5 601 200 200 100
1++:
	./$(NAME) 200 601 200 200 3
2:
	./$(NAME) 5 600 200 200 10
2+:
	./$(NAME) 5 600 200 200 100
2++:
	./$(NAME) 200 600 200 200 3
3:
	./$(NAME) 5 610 200 2 10
3+:
	./$(NAME) 5 610 200 2 100
3++:
	./$(NAME) 200 610 200 2 3
0-:
	./$(NAME) 5 600 600 600 5
1-:
	./$(NAME) 5 600 400 300 5
2-:
	./$(NAME) 5 7 2 2 5

.PHONY: all clean fclean re \
		0 1 1+ 1++ 2 2+ 2++ 3 3+ 3++ \
		0- 1- 2-