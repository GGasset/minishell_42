# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 12:49:28 by ggasset-          #+#    #+#              #
#    Updated: 2025/03/27 17:15:12 by ggasset-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
TEST_NAME=test

libft_NAME=./libft/libft.a
ARCHIVES= ${libft_NAME}

O_FILES=shell_get_word.o ft_shell_replace.o ft_normalize_spaces.o envp_search.o text_utils.o state_machine_utils.o
MAIN_O=
TEST_MAIN_O=test_main.o

CC_SECURITY_FLAGS= -Wall -Wextra -Werror
CC_FLAGS= -g -I ./libft/
LINKING_FLAGS= -I ./libft/

LOGO=\n ▗▄▄▄▄▖    ▗▄▄▄▄▖\n▐▌        ▐▌ \n▐▌ ▝▝▜▌   ▐▌ ▝▝▜▌\n▝▚▄▄▄▞▘   ▝▚▄▄▄▞▘     \n

all: libft ${NAME}

${NAME}: ${MAIN_O} ${O_FILES} ${ARCHIVES}
	cc ${LINKING_FLAGS} -o ${NAME} ${MAIN_O} ${O_FILES} ${ARCHIVES}

${TEST_NAME}: libft ${TEST_MAIN_O} ${O_FILES} ${ARCHIVES}
	cc ${LINKING_FLAGS} -o ${TEST_NAME} ${TEST_MAIN_O} ${O_FILES} ${ARCHIVES}

%.o: %.c
	cc ${CC_FLAGS} ${CC_SECURITY_FLAGS} -c $?

re: fclean all

fclean: clean
	rm -f ${NAME}

clean: libft-fclean
	rm -f ${O_FILES} ${TEST_MAIN_O} ${MAIN_O}

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
