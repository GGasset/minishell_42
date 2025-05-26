# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apaz-pri <apaz-pri@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 12:49:28 by ggasset-          #+#    #+#              #
#    Updated: 2025/05/26 12:16:19 by ggasset-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
TEST_NAME=test
UNAME := $(shell uname)

libft_NAME=./libft/libft.a
ARCHIVES= ${libft_NAME}

O_FILES=signal_prep2.o signal_prep.o envp_search.o


PARSING_FUNCTIONALITY_O_FILES=shell_get_word.o ft_shell_replace.o ft_normalize_spaces.o shell_split.o heredoc.o

PARSING_O_FILES=tokenizer.o parser.o
PARSING_O_FILES += $(addprefix Functionality/, ${PARSING_FUNCTIONALITY_O_FILES})
O_FILES += $(addprefix Parsing/, ${PARSING_O_FILES})


FUNCTIONALITY_O_FILES=dealloc.o file_utils.o is_operator.o text_utils.o get_paths.o

O_FILES += ${BUILTIN_O_FILES}
O_FILES += ${FUNCTIONALITY_O_FILES}

BUILT_IN_O_FILES=cd.o echo.o env.o exit.o export.o pwd.o unset.o
EXECUTION_O_FILES=errors.o execution.o built-in.o command.o pipes.o previusly.o
EXECUTION_O_FILES += $(addprefix Built-In/, ${BUILT_IN_O_FILES})
O_FILES += $(addprefix Execution/, ${EXECUTION_O_FILES})

MAIN_O=main.o
TEST_MAIN_O=test_main.o

INCLUDE= -I . -I ./libft/ -I ./headers/

SHARED_FLAGS=#-fsanitize=address,undefined
CC_SECURITY_FLAGS= ${SHARED_FLAGS} -Werror -Wall -Wextra
CC_FLAGS= -g ${INCLUDE}
LINKING_FLAGS= ${INCLUDE} ${SHARED_FLAGS} -lreadline

ifeq ($(UNAME),Darwin)
	INCLUDE += -I/usr/local/opt/readline/include
    LINKING_FLAGS += -L/usr/local/opt/readline/lib
endif

#------------- COLORS -------------

NC=\033[0m
On_UIGreen=\033[4;102m
On_IGreen=\033[0;102m
UGreen=\033[4;32m
IGreen=\033[0;92m
IYellow=\033[0;93m
UYellow=\033[4;33m
BLUE := \033[0;34m

LOGO=\n ▗▄▄▄▄▖    ▗▄▄▄▄▖\n▐▌        ▐▌ \n▐▌ ▝▝▜▌   ▐▌ ▝▝▜▌\n▝▚▄▄▄▞▘   ▝▚▄▄▄▞▘     \n

all: libft ${NAME}

${NAME}: ${MAIN_O} ${O_FILES} ${ARCHIVES}
	@cc ${LINKING_FLAGS} -o ${NAME} ${MAIN_O} ${O_FILES} ${ARCHIVES}
	@printf "\n$(IYellow)Executable: $(UYellow)%s$(IYellow) Created$(NC)\n" $@

%.o: %.c
	@len=$$(printf "%s" "$<" | wc -c); printf "$(IGreen)\rCompiling: $(UGreen)%*s$(NC) 🔨\033[K" "$$len" "$<"
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
