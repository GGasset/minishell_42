# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 12:49:28 by ggasset-          #+#    #+#              #
#    Updated: 2025/04/24 14:01:56 by apaz-pri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
TEST_NAME=test

libft_NAME=./libft/libft.a
ARCHIVES= ${libft_NAME}

O_FILES=cd.o export.o pwd.o echo.o parser.o get_paths.o execution.o heredoc.o dealloc.o file_utils.o shell_split.o is_operator.o tokenizer.o shell_get_word.o ft_shell_replace.o ft_normalize_spaces.o envp_search.o text_utils.o

MAIN_O=main.o
TEST_MAIN_O=test_main.o

CC_SECURITY_FLAGS= -Wall -Wextra -fsanitize=address
CC_FLAGS= -g -I ./libft/
LINKING_FLAGS= -I ./libft/ -lreadline -fsanitize=address

#------------- COLORS -------------

NC=\033[0m
On_UIGreen=\033[4;102m
On_IGreen=\033[0;102m
UGreen=\033[4;32m
IGreen=\033[0;92m
IYellow=\033[0;93m 
UYellow=\033[4;33m

LOGO=\n ▗▄▄▄▄▖    ▗▄▄▄▄▖\n▐▌        ▐▌ \n▐▌ ▝▝▜▌   ▐▌ ▝▝▜▌\n▝▚▄▄▄▞▘   ▝▚▄▄▄▞▘     \n

all: libft ${NAME}

${NAME}: ${MAIN_O} ${O_FILES} ${ARCHIVES}
	cc ${LINKING_FLAGS} -o ${NAME} ${MAIN_O} ${O_FILES} ${ARCHIVES}

${TEST_NAME}: libft ${TEST_MAIN_O} ${O_FILES} ${ARCHIVES}
	cc ${LINKING_FLAGS} -o ${TEST_NAME} ${TEST_MAIN_O} ${O_FILES} ${ARCHIVES}

%.o: %.c
	@echo "$(IGreen)Compiling: $(UGreen)$(notdir $<)${NC} 🔨"
	@cc ${CC_FLAGS} ${CC_SECURITY_FLAGS} -c $?

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
