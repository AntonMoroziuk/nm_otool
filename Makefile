# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/29 14:28:47 by amoroziu          #+#    #+#              #
#    Updated: 2018/12/29 14:37:37 by amoroziu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM = nm

OTOOL = otool

# srcs, path and obj

SRC_NM			=	nm.c \
					parse_load_commands.c \
					error.c

SRC_OTOOL		= otool.c
SRC_P 			= ./src/
OBJ_NM 			= $(addprefix $(OBJ_P),$(SRC_NM:.c=.o))
OBJ_OTOOL 		= $(addprefix $(OBJ_P),$(SRC_OTOOL:.c=.o))
OBJ_P			= ./obj/
INC_N			= nm.h otool.h
INC 			= $(addprefix -I, $(INC_P))
INC_P			= ./includes/
HEADERS			= $(addprefix $(INC_P),$(INC_N))

# libft

LIB_P			= ./libft/
ADD_LIB			= $(addprefix $(LIB_P),libft.a)
INC_LIB			= -I ./libft
LNK_LIB			= -L ./libft -l ftprintf

# compiler

CC 				= gcc
CC_FLAGS 		= -g -Wall -Wextra -Werror

all: obj $(ADD_LIB) $(NM) $(OTOOL)

obj:
	@mkdir -p $(OBJ_P)

$(OBJ_P)%.o:$(SRC_P)%.c $(HEADER)
	@$(CC) $(CC_FLAGS) $(INC_LIB) -I $(INC_P) -o $@ -c $<

$(ADD_LIB):
	@make -C $(LIB_P)

$(NM): $(OBJ_NM)
	@$(CC) $(LNK_LIB) $(OBJ_NM) -o $(NM)

$(OTOOL): $(OBJ_NM)
	@$(CC) $(LNK_LIB) $(OBJ_OTOOL) -o $(OTOOL)


clean:
	@rm -rf $(OBJ_P)
	@make -C $(LIB_P) clean

fclean: clean
	@rm -rf $(NM) $(OTOOL)
	@make -C $(LIB_P) fclean

re: fclean all

.PHONY: all clean fclean re
