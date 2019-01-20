# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/08 12:10:45 by mguerrea          #+#    #+#              #
#    Updated: 2019/01/08 12:13:48 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE	:= make
CC		:= gcc
LD		:= gcc
RM		:= rm -rf

SRCDIR	:=	./
INCLDIR	:=	-I libft/includes
LIBDIR 	:=	libft/

CFLAGS	:=	-Wall -Wextra -Werror $(INCLDIR)
LDFLAGS	:=	-L$(LIBDIR) -lft

SRCS    :=	basics.c bin.c builtin.c cd.c environ.c errors.c format.c free.c get_next_line.c  \
			init.c main.c prompt.c split.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(patsubst %.c,%.o,$(SRCS))
DEPS	:=	Makefile minishell.h
LIB		:=	$(LIBDIR)/libft.a
NAME	:=	minishell

all: $(NAME)

$(LIB):
	@$(MAKE) -C libft/

$(NAME): $(LIB) $(OBJS)
	@echo "\033[32m  Creating: \033[0m$(NAME)"
	@$(LD) $(LDFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(DEPS)
	@printf "\033[32m Compiling: \033[0m$< -> $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "\033[32m  Cleaning: \033[0m$(OBJS)\033[0m\n"
	@$(RM) $(OBJS)
	@$(MAKE) -C libft clean

fclean: clean
	@printf "\033[32m  Removing: \033[0m"
	@find . -name "minishell" -exec sh -c 'basename {}' \; | tr "\n" " "
	@echo ""
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re