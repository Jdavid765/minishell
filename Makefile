# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 17:29:05 by canoduran         #+#    #+#              #
#    Updated: 2026/04/03 19:08:31 by canoduran        ###   ########.fr        #
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
CFLAGS   = -Wall -Wextra -Werror -fPIE -fsanitize=address -fsanitize=undefined
LFLAGS   = -lreadline -lncurses -ltinfo
DIRINC   = include
INCLUDES = -I$(DIRINC)
HEADER   = $(DIRINC)/minishell.h
LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

ifeq ($(OS), Darwin)
	LFLAGS = -L /opt/homebrew/Cellar/readline/8.3.3/lib -lreadline -lncurses
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
DIR_NODE   = node
DIR_CLEAN  = clean
DIR_ENV    = env


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
      $(DIR_SRC)/$(DIR_EXEC)/find_path_in_env.c \
      $(DIR_SRC)/$(DIR_EXEC)/rebuild_env.c \
      $(DIR_SRC)/$(DIR_PARSING)/parsing.c \
	  $(DIR_SRC)/$(DIR_PARSING)/next_parsing.c \
	  $(DIR_SRC)/$(DIR_PARSING)/last_parsing.c \
      $(DIR_SRC)/$(DIR_SIG)/signal.c \
      $(DIR_SRC)/$(DIR_UTILS)/utils.c \
      $(DIR_SRC)/$(DIR_UTILS)/check_cmd.c \
      $(DIR_SRC)/$(DIR_SETUP)/setup.c \
      $(DIR_SRC)/$(DIR_TOKEN)/find_token_in_readline.c \
      $(DIR_SRC)/$(DIR_TOKEN)/find_token_by_char.c \
      $(DIR_SRC)/$(DIR_NODE)/functions_env.c \
      $(DIR_SRC)/$(DIR_NODE)/node_pars.c \
      $(DIR_SRC)/$(DIR_ENV)/export_env.c \
      $(DIR_SRC)/$(DIR_ENV)/exp_variable.c \
	  $(DIR_SRC)/$(DIR_ENV)/next_exp_var.c \
	  $(DIR_SRC)/$(DIR_ENV)/utils_exp_var.c \
	  $(DIR_SRC)/$(DIR_CLEAN)/clean_node.c \
	  $(DIR_SRC)/$(DIR_CLEAN)/clean_utils.c \
	  
#       $(DIR_SRC)/$()/.c \

# --- OBJECTS ---
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)


# --- RULES ---

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@printf "$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(GREEN)Build successfully complete!$(RESET)\n"

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory
	@printf "$(BLUE)adding libft$<...$(RESET)\n"

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@printf "$(BLUE)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) --no-print-directory

fclean: clean
	@printf "$(RED)Removing executable $(NAME)...$(RESET)\n"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) --no-print-directory

re : fclean all

.PHONY : all clean fclean re