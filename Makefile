##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## To compile File
##

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	pong

CSFML	=	-lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CSFML)

clean:	$(OBJ)
	rm -f $(OBJ)
	rm -f *~

fclean:	clean
	rm -f $(NAME)
	rm -f *~

re:	all clean
