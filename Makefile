# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 12:49:28 by ggasset-          #+#    #+#              #
#    Updated: 2025/03/19 15:57:18 by ggasset-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

libft_NAME=./libft/libft.a
ARCHIVES= ${libft_NAME}

O_FILES= test_main.o ft_shell_replace.o

CC_SECURITY_FLAGS= -Wall -Wextra -Werror
CC_FLAGS= -g -I ./libft/
LINKING_FLAGS= -I ./libft/

LOGO=\n ▗▄▄▄▄▖    ▗▄▄▄▄▖\n▐▌        ▐▌ \n▐▌ ▝▝▜▌   ▐▌ ▝▝▜▌\n▝▚▄▄▄▞▘   ▝▚▄▄▄▞▘     \n

all: libft ${NAME}

${NAME}: ${O_FILES} ${ARCHIVES}
	cc ${LINKING_FLAGS} -o ${NAME} ${O_FILES} ${ARCHIVES}

%.o: %.c
	cc ${CC_FLAGS} ${CC_SECURITY_FLAGS} -c $?

re: fclean all

fclean: clean
	rm -f ${NAME}

clean: libft-fclean
	rm -f ${O_FILES}

# LIBFT

libft:
	make --directory=./libft/ all

libft-re: libft-fclean libft

libft-clean:
	make --directory=./libft/ clean

libft-fclean:
	make --directory=./libft/ fclean

logo:
	@echo "${LOGO}"
	@sleep .25

.PHONY: all re fclean clean libft libft-re libft-clean libft-fclean logo
