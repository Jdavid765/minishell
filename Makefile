# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 17:29:05 by canoduran         #+#    #+#              #
#    Updated: 2026/03/10 19:11:06 by canoduran        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- COLORS ---
RED      = \033[0;31m
BLUE     = \033[0;34m
GREEN    = \033[0;32m
RESET    = \033[0m

# --- VARIABLES ---
OS = $(shell uname)
CC = gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
INCLUDES = -I.

ifeq ($(OS), Darwin)
	LFLAGS = -L /opt/homebrew/Cellar/readline/8.3.3/lib -lreadline
	INCLUDES = -I /opt/homebrew/Cellar/readline/8.3.3/include
endif

# --- DIRECTORIES ---
DIRSRC     = src
DIRPARSING = parsing
DIRBUILTIN = builtins
DIRSIG     = signal
DIRUTILS   = utils
DIREXEC    = exec
OBJ_DIR    = obj


# --- SOURCES ---
SRC = $(DIRSRC)/main.c \
      $(DIRSRC)/$(DIRBUILTIN)/cd_builtin.c \
      $(DIRSRC)/$(DIRBUILTIN)/echo_builtin.c \
      $(DIRSRC)/$(DIRBUILTIN)/env_builtin.c \
      $(DIRSRC)/$(DIRBUILTIN)/exit_builtin.c \
      $(DIRSRC)/$(DIRBUILTIN)/export_builtin.c \
      $(DIRSRC)/$(DIRBUILTIN)/pwd_builtin.c \
      $(DIRSRC)/$(DIRBUILTIN)/unset_builtin.c \
      $(DIRSRC)/$(DIREXEC)/exec.c \
      $(DIRSRC)/$(DIRPARSING)/parsing.c \
      $(DIRSRC)/$(DIRSIG)/signal.c \
      $(DIRSRC)/$(DIRUTILS)/utils.c \
	  $(DIRSRC)/$(DIRUTILS)/check_cmd.c \
#       $(DIRSRC)/$()/.c \


# --- OBJECTS ---
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)


# --- RULES ---

all : $(NAME)

$(NAME) : $(OBJ)
	@echo -e "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -o $(NAME)
	@echo -e "$(GREEN)Build successfully complete!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)


fclean: clean
	@echo -e "$(RED)Removing executable $(NAME)...$(RESET)"
	@rm -f $(NAME)


re : fclean all

.PHONY : all clean fclean re