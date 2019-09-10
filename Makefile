# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 14:03:15 by jgourdin          #+#    #+#              #
#    Updated: 2019/09/10 16:29:18 by gmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_NAME = basics.c bin.c builtin.c cd.c environ.c errors_1.c format.c free.c \
	token_list.c lexer.c parser.c output_input.c init.c main.c prompt.c \
	command_line.c buffer.c history.c array_functions.c cursor.c signal.c \
	copy.c fd.c parser_redir.c command_list.c command_list_2.c heredoc.c \
	errors_2.c pipe.c trimquotes.c lexer_operator.c

INC_NAME = minishell.h sh_parser.h

INC_PATH = ./includes

INC_FLAGS = -I./includes -I./libft/includes

LIB_FLAGS = -L./libft

LIBS = -lft -lncurses

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

SRC_PATH = src

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = obj

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(subst $(SRC_PATH),$(OBJ_PATH),$(OBJ_NAME))

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

RED = \x1B[31m
GRN = \x1B[32m
YEL = \x1B[33m
BLU = \x1B[34m
MAG = \x1B[35m
CYN = \x1B[36m
WHT = \x1B[37m
RESET = \x1B[0m
ERASE = \033[2K

all: $(NAME)

libftmake:
	@make -C ./libft --no-print-directory

$(NAME): $(OBJ) | libftmake
	@$(CC) $(LIB_FLAGS) $(LIBS) -o $@ $(OBJ)
	@echo "\n$(BLU)[$(NAME)]$(GRN) Compilation success$(RESET)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<
	@echo "\r$(ERASE)$(BLU)[$(NAME)]$(RESET) $@ created\c"

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(OBJ_PATH)
	@make -C ./libft clean --no-print-directory
	@echo "$(BLU)[$(NAME)]$(RED) .o files deleted$()$(RESET)"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LINKNAME)
	@make -C ./libft fclean --no-print-directory
	@echo  "$(BLU)[$(NAME)]$(RED) executable file deleted$(RESET)"

re: fclean $(NAME)

.PHONY: all, clean, fclean, re, lib
