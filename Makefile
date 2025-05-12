# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 12:49:28 by ggasset-          #+#    #+#              #
#    Updated: 2025/05/12 18:27:28 by apaz-pri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
TEST_NAME=test

libft_NAME=./libft/libft.a
ARCHIVES= ${libft_NAME}

O_FILES=signal_prep.o envp_search.o


PARSING_FUNCTIONALITY_O_FILES=shell_get_word.o ft_shell_replace.o ft_normalize_spaces.o shell_split.o heredoc.o

PARSING_O_FILES=tokenizer.o parser.o
PARSING_O_FILES += $(addprefix Functionality/, ${PARSING_FUNCTIONALITY_O_FILES})
O_FILES += $(addprefix Parsing/, ${PARSING_O_FILES})


FUNCTIONALITY_O_FILES=dealloc.o file_utils.o is_operator.o text_utils.o get_paths.o

O_FILES += ${BUILTIN_O_FILES}
O_FILES += ${FUNCTIONALITY_O_FILES}

BUILT_IN_O_FILES=cd.o echo.o env.o exit.o export.o pwd.o unset.o
EXECUTION_O_FILES=execution.o
EXECUTION_O_FILES += $(addprefix Built-In/, ${BUILT_IN_O_FILES})
O_FILES += $(addprefix Execution/, ${EXECUTION_O_FILES})

MAIN_O=main.o
TEST_MAIN_O=test_main.o

INCLUDE= -I . -I ./libft/ -I ./headers/

CC_SECURITY_FLAGS= -Wall -Wextra #-fsanitize=address
CC_FLAGS= -g ${INCLUDE}
LINKING_FLAGS= ${INCLUDE} -lreadline #-fsanitize=address

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
	@cc ${LINKING_FLAGS} -o ${NAME} ${MAIN_O} ${O_FILES} ${ARCHIVES}

${TEST_NAME}: libft ${TEST_MAIN_O} ${O_FILES} ${ARCHIVES}
	@cc ${LINKING_FLAGS} -o ${TEST_NAME} ${TEST_MAIN_O} ${O_FILES} ${ARCHIVES}

%.o: %.c
	@len=$$(printf "%s" "$<" | wc -c); printf "$(IGreen)\rCompiling: $(UGREEN)%*s$(NC) 🔨\033[K" "$$len" "$<"
	@cc ${CC_FLAGS} ${CC_SECURITY_FLAGS} -o $@ -c $?

re: fclean all

fclean: clean
	@rm -f ${NAME}

clean: libft-fclean
	@rm -f ${O_FILES} ${TEST_MAIN_O} ${MAIN_O}

# LIBFT

libft:
	@make --no-print-directory --directory=./libft/ all

libft-re: libft-fclean libft

libft-clean:
	@make --no-print-directory --directory=./libft/ clean

libft-fclean:
	@make --no-print-directory --directory=./libft/ fclean

logo:
	@echo "${LOGO}"
	@sleep .25

.PHONY: all re fclean clean libft libft-re libft-clean libft-fclean logo
