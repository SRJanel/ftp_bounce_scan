##
## Makefile for Makefile
## 
## Made by SRJanel
## Login SRJanel <n******.******s@epitech.eu>
## 
## Started on  Mon Nov  6 11:27:34 2017 
## Last update Mon Dec  4 18:27:07 2017 
##

SRC	= src/main.c \
	src/utils.c \
	src/options.c \
	src/ftp_scan.c \
	src/network/utils.c \
	src/build_cmd.c \

OBJ	= $(SRC:.c=.o)

NAME	= ftp_bounce_scan

RM	= rm -f

CC	= gcc

CFLAGS	+= -Wall -Wextra -Werror
CFLAGS	+= -ansi # -pedantic-errors
CFLAGS	+= -I./include
CFLAGS	+= -D_GNU_SOURCE
#CFLAGS	+= -ggdb3 -g3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
