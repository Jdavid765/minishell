# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: canoduran <canoduran@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 17:29:05 by canoduran         #+#    #+#              #
#    Updated: 2026/03/09 23:28:30 by canoduran        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- COLORS ---
RED      = \033[0;31m
BLUE     = \033[0;34m
GREEN    = \033[0;32m
RESET    = \033[0m

# --- VARIABLES ---
CC       = gcc
NAME     = minishell
CFLAGS   = -Wall -Wextra -Werror
LFLAGS    = -lreadline
DIRINC     = include
INCLUDES = -I$(DIRINC)
HEADER   = $(DIRINC)/minishell.h

# --- DIRECTORIES ---

DIRSRC     = src
DIRPARSING = parsing
DIRBUILTIN = builtins
DIRSIG     = signal
DIRUTILS   = utils
DIREXEC    = exec
OBJ_DIR    = obj
DIR_SETUP  = setup


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
<<<<<<< HEAD
<<<<<<< HEAD
	  $(DIRSRC)/$(DIRUTILS)/check_cmd.c \
=======
=======
      $(DIRSRC)/$(DIRUTILS)/check_cmd.c \
>>>>>>> a4d56f6 (adding pwd builtin)
      $(DIRSRC)/$(DIR_SETUP)/setup.c \
>>>>>>> 3fc7d38 (bugged makefile and failed squash)
#       $(DIRSRC)/$()/.c \

# --- OBJECTS ---
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)


# --- RULES ---

all : $(NAME)

$(NAME) : $(OBJ)
	@echo -e "$(BLUE)Linking $(NAME)...$(RESET)"
<<<<<<< HEAD
	@$(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -o $(NAME)
=======
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LFLAGS)
>>>>>>> 3fc7d38 (bugged makefile and failed squash)
	@echo -e "$(GREEN)Build successfully complete!$(RESET)"

$(OBJ_DIR)/%.o: %.c $(HEADER)
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