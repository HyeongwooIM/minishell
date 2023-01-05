# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 12:25:30 by him               #+#    #+#              #
#    Updated: 2023/01/05 09:34:39 by woohyeong        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = libft
SRCS = $(addprefix ./mandatory/, ${SRCS_FILES})
SRCS_FILES = minishell.c
SRCS_BONUS = $(addprefix ./bonus/, ${BONUS_FILES})
BONUS_FILES = 	
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(SRCS_BONUS:.c=.o)
NAME = minishell
BONUS_NAME = pipex_bonus
ifdef WITH_BONUS
    TOTAL_OBJS = $(BONUS_OBJS)
	NAME = $(BONUS_NAME)
else
    TOTAL_OBJS = $(OBJS)
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^	

$(NAME) : $(TOTAL_OBJS)
	make re -C .libft
	$(CC) $(CFLAGS) $(TOTAL_OBJS) -Llibft -lft -o ${NAME}

clean :
	make fclean -C ./libft
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
	make fclean -C ./libft
	rm -rf $(NAME) $(BONUS_NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re%