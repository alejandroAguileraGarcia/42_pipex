NAME	= pipex

SRCS	=	ft_split.c ft_strutils.c ft_utils.c pipex.c

OBJS	=	${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

all: $(NAME)

$(NAME):	${OBJS}
		${CC} ${CFLAGS} ${SRCS} -o ${NAME}
		
clean:
			${RM} ${OBJS}

fclean:		clean
				${RM} ${NAME}

re:			fclean all

.PHONY: all, clean, fclean, re
