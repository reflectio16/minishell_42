# **************************************************************************** #
#                                  MINISHELL                                   #
# **************************************************************************** #

NAME		= minishell
# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3

# Project directories
SRC_DIR		=	src
INC_DIR		=	include
LIBFT_DIR	=	Libft

# Subdirectories
PARSING_DIR	=	$(SRC_DIR)/parsing
EXEC_DIR	=	$(SRC_DIR)/exec
BUILTIN_DIR	=	$(SRC_DIR)/builtin
UTILS_DIR	=	$(SRC_DIR)/utils

# Source files
SRC_FILES	=	$(SRC_DIR)/main.c \
				$(PARSING_DIR)/lexer.c \
				$(UTILS_DIR)/lexer_utils.c \

# Object files
OBJS		=	$(SRC_FILES:.c=.o)

# Libft
LIBFT		=	$(LIBFT_DIR)/libft.a

# Colors
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RESET		=	\033[0m

# ---------------------- Rules ----------------------

all: $(LIBFT) $(NAME)

# Compile Libft
$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# Build minishell
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "$(GREEN)✅ Minishell built successfully!$(RESET)"

# Compile .c -> .o
%.o: %.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Clean object files
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@for f in $(OBJS); do \
		if [ -f "$$f" ]; then rm -f "$$f"; fi; \
	done
	@echo "$(YELLOW)🧹 Cleaned object files$(RESET)"

# Full clean
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(YELLOW)🧼 Full clean complete$(RESET)"

# Rebuild
re: fclean all

.PHONY: all clean fclean re
