#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smonroe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 07:25:53 by smonroe           #+#    #+#              #
#    Updated: 2019/02/04 01:48:15 by amontano         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = kift_app

SRC = kift/client_app.c

LOGGER = server/log_line

LOGSRC = server/logger.c

all: $(NAME)

$(NAME):
	@echo "\033[33mMaking KIFT Project\033[0m"
	@make -C libft
	gcc -Wall -Werror -Wextra -o $(NAME) -L libft -lft -I libft $(SRC) -g -fsanitize=address
	gcc -Wall -Werror -Wextra -o $(LOGGER) -L libft -lft -I libft $(LOGSRC) -g -fsanitize=address
	@echo "\033[33mInitializing Environment\033[0m"
	@/bin/sh init_env.sh
	@echo "\033[32mFinished Application build."
	@echo "\033[32mRun ./kift_app to being\033[0m"

clean:
	make clean -C libft
	/bin/rm -rf *~ *.o \#*\# *.swp *.gch a.out *.dSYM

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME) $(LOGGER)

re: fclean all
