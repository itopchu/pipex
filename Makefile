# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: itopchu <itopchu@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/18 15:16:33 by itopchu       #+#    #+#                  #
#    Updated: 2022/12/18 15:16:33 by itopchu       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

EXEC	= pipex
#******************************************************************************#
INC		= include/
LIBFT	= include/libft
#******************************************************************************#
SRC_DIR	= ./src/
SRC		= $(addprefix $(SRC_DIR), $(SRC_F))
SRC_F	=	main.c \
			utils.c

OBJ		= ${SRC:.c=.o}
#******************************************************************************#
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f
#******************************************************************************#
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -I $(INC) -I $(LIBFT) -o $@

$(EXEC): $(OBJ)
	@$(MAKE) bonus -C $(LIBFT)
	@$(CC) -o $(EXEC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a
#******************************************************************************#
all		: $(EXEC)

debug	: CFLAGS = -g -fsanitize=address
debug	: fclean all

clean	:
	@$(MAKE) -C $(LIBFT) clean
	@$(RM) $(OBJ)

fclean	: clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(RM) $(EXEC)

re		: fclean all

.PHONY	: all, clean, fclean, re
