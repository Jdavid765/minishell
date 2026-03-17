# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 17:29:05 by canoduran         #+#    #+#              #
#    Updated: 2026/03/17 15:01:04 by canoduran        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- COLORS ---
RED      = \033[0;31m
BLUE     = \033[0;34m
GREEN    = \033[0;32m
RESET    = \033[0m

# --- VARIABLES ---
OS = $(shell uname)
CC       = gcc
NAME     = minishell
CFLAGS   = -Wall -Wextra -Werror
LFLAGS   = -lreadline
DIRINC   = include
INCLUDES = -I$(DIRINC)
HEADER   = $(DIRINC)/minishell.h
LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

ifeq ($(OS), Darwin)
	LFLAGS = -L /opt/homebrew/Cellar/readline/8.3.3/lib -lreadline
	INCLUDES = -I /opt/homebrew/Cellar/readline/8.3.3/include
endif

# --- DIRECTORIES ---

DIR_SRC     = src
DIR_PARSING = parsing
DIR_BUILTIN = builtins
DIR_SIG     = signal
DIR_UTILS   = utils
DIR_EXEC    = exec
DIR_TOKEN   = token
OBJ_DIR    = obj
DIR_SETUP  = setup
DIR_NODE   = noeud
DIR_CMD    = cmd


# --- SOURCES ---
SRC = $(DIR_SRC)/main.c \
      $(DIR_SRC)/$(DIR_BUILTIN)/cd_builtin.c \
      $(DIR_SRC)/$(DIR_BUILTIN)/echo_builtin.c \
      $(DIR_SRC)/$(DIR_BUILTIN)/env_builtin.c \
      $(DIR_SRC)/$(DIR_BUILTIN)/exit_builtin.c \
      $(DIR_SRC)/$(DIR_BUILTIN)/export_builtin.c \
      $(DIR_SRC)/$(DIR_BUILTIN)/pwd_builtin.c \
      $(DIR_SRC)/$(DIR_BUILTIN)/unset_builtin.c \
      $(DIR_SRC)/$(DIR_EXEC)/exec.c \
      $(DIR_SRC)/$(DIR_PARSING)/parsing.c \
      $(DIR_SRC)/$(DIR_SIG)/signal.c \
      $(DIR_SRC)/$(DIR_UTILS)/utils.c \
      $(DIR_SRC)/$(DIR_UTILS)/check_cmd.c \
      $(DIR_SRC)/$(DIR_SETUP)/setup.c \
      $(DIR_SRC)/$(DIR_TOKEN)/find_token_in_readline.c \
      $(DIR_SRC)/$(DIR_TOKEN)/find_token_by_char.c \
	  $(DIR_SRC)/$(DIR_NODE)/functions_env.c \
	  $(DIR_SRC)/$(DIR_CMD)/cmd.c
#       $(DIR_SRC)/$()/.c \

# --- OBJECTS ---
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)


# --- RULES ---

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@echo -e "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo -e "$(GREEN)Build successfully complete!$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo -e "$(BLUE)adding libft$<...$(RESET)"

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo -e "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) --no-print-directory

fclean: clean
	@echo -e "$(RED)Removing executable $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) --no-print-directory

re : fclean all

.PHONY : all clean fclean re