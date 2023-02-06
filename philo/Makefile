# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 15:12:51 by oheinzel          #+#    #+#              #
#    Updated: 2023/02/03 13:24:05 by oheinzel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm -f

GREEN		= \033[0;32m
CYAN		= \033[0;36m
WHITE		= \033[0m

SRC_FILES	= main utils routine

SRC			=	$(addsuffix .c, $(SRC_FILES))
OBJ			=	$(addsuffix .o, $(SRC_FILES))

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
			@echo "$(GREEN)philo compiled!$(WHITE)"

%.o:%.c
			@echo "$(CYAN)Compiling $(WHITE): $<"
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) $(OBJ)
			@echo "$(GREEN)philo object files cleaned!$(WHITE)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(GREEN)philo executable files cleaned!$(WHITE)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for philo!$(WHITE)"

.PHONY:		all clean fclean re
