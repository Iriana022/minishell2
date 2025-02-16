# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 12:06:42 by pmihangy          #+#    #+#              #
#    Updated: 2024/10/23 08:58:16 by irazafim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## ARGUMENTS
NAME = minishell
SRC = main.c 
SRC_FILES = $(addprefix src/, $(SRC))
LEXER_FILES = lexer.c expander.c
AST_BUILDER_FILES = parser.c
PARSER_FILES = bool.c list_manip.c utils.c
PARSER_FILES += $(addprefix lexer/, $(LEXER_FILES))
PARSER_FILES += $(addprefix ast_builder/, $(AST_BUILDER_FILES))
UTILS_FILES = error.c utils.c verif_if_cmd_exist.c exec.c
EXECUTION_FILES =  ## TODO
BUILTINS_FILES = echo.c env.c export.c unset.c exit.c pwd.c cd.c
SRC_FILES += $(addprefix src/utils/, $(UTILS_FILES))
SRC_FILES += $(addprefix src/parser/, $(PARSER_FILES))
SRC_FILES += $(addprefix src/execution/, $(EXECUTION_FILES))
SRC_FILES += $(addprefix src/builtins/, $(BUILTINS_FILES))
CC = cc -g
CFLAGS = -Wall -Wextra #-Werror
RM = rm -rf
INCLUDE = -I./include -I./libft
LIBFT = ./libft
LINKING = -L$(LIBFT) -lft -lreadline

## RULES
all: $(NAME)

$(NAME): $(SRC_FILES)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC_FILES) -o $(NAME) $(LINKING)

clean:
	make -C $(LIBFT) clean
	$(RM) *.o

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
