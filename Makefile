SRC=    get_path.c	\
		split.c       		\
		pipex.c      \
		str_cmp.c      \
		strcat.c    \



NAME= pipex

OBJETS= ${SRC:.c=.o}


gcc=gcc -Werror -Wall -Wextra

$(NAME):    ${OBJETS}	

%.o: %.c
	${gcc} -o $@ -c $<
	

all: ${NAME}

re: fclean all

clean:
		rm -f ${OBJETS} 

fclean: clean
		rm -f ${NAME}

.PHONY: all clean fclean re