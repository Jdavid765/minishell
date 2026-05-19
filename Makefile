# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfiora-d                                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 17:29:05 by canoduran         #+#    #+#              #
#    Updated: 2026/05/19 11:21:00 by nfiora-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- COLORS ---
RED      = \033[0;31m
BLUE     = \033[0;34m
GREEN    = \033[0;32m
RESET    = \033[0m

# --- VARIABLES ---
OS = $(shell uname)
CC       = cc
NAME     = minishell
CFLAGS   = -Wall -Wextra -Werror
LFLAGS   = -lreadline 
DIRINC   = include
INCLUDES = -I$(DIRINC)
HEADER   = $(DIRINC)/minishell.h
LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

ifeq ($(OS), Darwin)
	LFLAGS = -L /opt/homebrew/opt/readline/lib -lreadline -lncurses
	INCLUDES = -I /opt/homebrew/opt/readline/include -I$(DIRINC)
endif

# --- DIRECTORIES ---
DIR_SRC     = src
DIR_BUILTIN = $(DIR_SRC)/builtins
DIR_CORE    = $(DIR_SRC)/core
DIR_ENV     = $(DIR_SRC)/env
DIR_EXEC    = $(DIR_SRC)/exec
DIR_EXP     = $(DIR_SRC)/expansion
DIR_LEXER   = $(DIR_SRC)/lexer
DIR_PARSER  = $(DIR_SRC)/parser
DIR_UTILS   = $(DIR_SRC)/utils
OBJ_DIR     = obj

# --- SOURCES ---
SRC = $(DIR_BUILTIN)/cd_builtin.c \
      $(DIR_BUILTIN)/echo_builtin.c \
      $(DIR_BUILTIN)/env_builtin.c \
      $(DIR_BUILTIN)/exit_builtin.c \
      $(DIR_BUILTIN)/export_builtin.c \
      $(DIR_BUILTIN)/export_utils.c \
      $(DIR_BUILTIN)/pwd_builtin.c \
      $(DIR_BUILTIN)/unset_builtin.c \
      $(DIR_CORE)/main.c \
      $(DIR_CORE)/setup.c \
      $(DIR_CORE)/signal.c \
      $(DIR_ENV)/env_init.c \
      $(DIR_ENV)/env_lst_utils.c \
      $(DIR_ENV)/env_utils.c \
      $(DIR_ENV)/next_exp_var.c \
      $(DIR_ENV)/rebuild_env.c \
      $(DIR_ENV)/utils_exp_var.c \
      $(DIR_EXEC)/exec.c \
      $(DIR_EXEC)/exec_builtins.c \
      $(DIR_EXEC)/exec_fds.c \
      $(DIR_EXEC)/exec_path.c \
      $(DIR_EXEC)/exec_pipeline.c \
      $(DIR_EXEC)/exec_simple.c \
      $(DIR_EXP)/expander_quotes.c \
      $(DIR_EXP)/expander_split.c \
      $(DIR_EXP)/expander_utils.c \
      $(DIR_EXP)/expender.c \
      $(DIR_LEXER)/lexer.c \
      $(DIR_LEXER)/lexer_handlers.c \
      $(DIR_LEXER)/lexer_nodes.c \
      $(DIR_LEXER)/lexer_quotes.c \
      $(DIR_LEXER)/lexer_redir.c \
      $(DIR_PARSER)/parser_heredoc.c \
      $(DIR_PARSER)/parser_nodes.c \
      $(DIR_PARSER)/parser_redirs.c \
      $(DIR_PARSER)/parser_utils.c \
      $(DIR_PARSER)/parsing.c \
      $(DIR_UTILS)/clean_core.c \
      $(DIR_UTILS)/clean_lists.c \
      $(DIR_UTILS)/utils.c

# --- OBJECTS ---
OBJ = $(SRC:$(DIR_SRC)/%.c=$(OBJ_DIR)/%.o)

# --- RULES ---
all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	@printf "$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(GREEN)Build successfully complete!$(RESET)\n"

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory
	@printf "$(BLUE)adding libft...$(RESET)\n"

$(OBJ_DIR)/%.o: $(DIR_SRC)/%.c $(HEADER)
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