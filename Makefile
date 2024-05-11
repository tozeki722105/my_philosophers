# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 21:32:36 by toshi             #+#    #+#              #
#    Updated: 2024/05/12 03:45:14 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo
CC			:=	cc -fsanitize=thread
# CFLAGS		:=	-Wall -Wextra -Werror 
PTHREAD_FLAGS	:=	-lpthread
SRC_PATHS	:=	./
SRCS		:=	$(foreach path, $(SRC_PATHS), $(wildcard $(path)*.c))
OUT_PATTERN	:=	
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
1:
	./$(NAME) 5 610 200 200 10
1+:
	./$(NAME) 5 610 200 200 100
2:
	./$(NAME) 5 601 200 200 10
2+:
	./$(NAME) 5 601 200 200 100
3:
	./$(NAME) 200 610 200 200 10
3+:
	./$(NAME) 200 610 200 200 100
4:
	./$(NAME) 5 610 200 2 10
4+:
	./$(NAME) 5 610 200 2 100
5:
	./$(NAME) 5 11 3 3 10
5+:
	./$(NAME) 5 11 3 3 100
6:
	./$(NAME) 5 121 40 40 10
6+:
	./$(NAME) 5 121 40 40 100
7:
	./$(NAME) 5 600 600 600 5

.PHONY: all clean fclean re