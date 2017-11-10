##
## Makefile for Makefile
## 
## Made by SRJanel
## Login SRJanel <n******.******s@epitech.eu>
## 
## Started on  Mon Nov  6 11:27:34 2017 
## Last update Fri Nov 10 18:05:55 2017 
##

SRC	= src/main.c \
	src/utils.c \

OBJ	= $(SRC:.c=.o)

NAME	= ftp_bounce_scan

RM	= rm -f

CC	= gcc

CFLAGS	+= -Wall -Wextra -Werror
CFLAGS	+= -ansi # -pedantic-errors
CFLAGS	+= -I./include
#CFLAGS	+= -ggdb3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
