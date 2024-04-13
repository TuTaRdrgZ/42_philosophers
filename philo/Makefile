# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 12:35:41 by bautrodr          #+#    #+#              #
#    Updated: 2024/04/13 10:42:59 by bautrodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[93m
CYAN = \033[96m

SRCS = main.c \
       utils.c \
	   utils2.c \
       check_input.c \
       state.c \
       init_philos.c \
	   print_state.c \
	   wait_all_threads.c \
	   supervisor.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wextra -Werror -pthread -g -fsanitize=thread

all: $(NAME)

%.o:%.c philo.h Makefile
	@printf "\033[0;33mGenerating philo objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) Makefile philo.h
	@echo "\n"
	@echo "$(YELLOW)Creating executable...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@echo "$(YELLOW)$(BOLD)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@echo "$(RED)$(BOLD)Object files removed!$(RESET)"

fclean: clean
	@echo "$(YELLOW)$(BOLD)Cleaning trash...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)$(BOLD)Trash removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
