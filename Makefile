# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: him <him@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 12:25:30 by him               #+#    #+#              #
#    Updated: 2023/01/27 12:04:15 by him              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra 
INCLUDES = -I./includes
#SRCS = $(addprefix ./mandatory/, ${SRCS_FILES})
SRCS = ${SRCS_FILES}
SRCS_FILES = parse/parse.c \
			 parse/chunks.c \
             parse/replace.c \
             parse/tokens.c \
             parse/cmds.c \
             parse/node.c \
             parse/utils.c \
             parse/utils2.c \
             parse/utils3.c \
             parse/signal.c \
             main.c \
             execute/builtin.c \
             execute/execute.c \
             execute/ft_cd.c \
             execute/ft_echo.c \
             execute/ft_env.c \
             execute/ft_exe.c \
             execute/ft_exit.c \
             execute/ft_export.c \
             execute/ft_fork.c \
             execute/ft_here_doc.c \
             execute/ft_unset.c \
             execute/ft_rdir.c \
             execute/ft_pwd.c \
             util/env.c \
             util/ft_error_exit.c \
             util/find_env.c \
             util/find_env_add.c \
             util/ft_strcmp.c \
             util/ft_strjoin2.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
TOTAL_OBJS = $(OBJS)
LIBFT = -Llibft -lft
READLINE_HDR = -I/Users/him/.brew/opt/readline/include
READLINE_LIB = -L/Users/him/.brew/opt/readline/lib -lreadline
all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_HDR) -c -o $@ $^

$(NAME) : $(TOTAL_OBJS)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(TOTAL_OBJS) $(INCLUDES) $(READLINE_HDR) $(READLINE_LIB) $(LIBFT) -o ${NAME}
	@echo	"🙋‍♀️🙋‍♂️ make"

clean :
	@make fclean -C ./libft
	@rm -rf $(OBJS)
	@echo	"🙋‍♀️🙋‍♂️ make clean"

fclean : clean
	@make fclean -C ./libft
	@rm -rf $(NAME)
	@echo	"🙋‍♀️🙋‍♂️ make fclean"

re :
	@make fclean
	@make all
	@echo	"🙋‍♀️🙋‍♂️ make re"

.PHONY : all bonus clean fclean re