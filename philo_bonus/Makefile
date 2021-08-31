# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/28 12:24:26 by gesperan          #+#    #+#              #
#    Updated: 2021/05/28 16:19:07 by gesperan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus
HEADERS	=	librab.h
FUNCS	=	firststep.c tools.c central.c utils.c
OBJS	=	${FUNCS:.c=.o}
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm
MAKES	=	makes
all: ${NAME}
${NAME}: ${OBJS} ${HEADERS}
	${CC} ${CFLAGS}  ${OBJS} -o ${NAME}
%.o : %.c ${HEADERS}
	${CC} -c ${CFLAGS} ${INCL} $< -o $@
clean:
	${RM} -f ${OBJS}
fclean: clean
	${RM} -f ${NAME}
re:	fclean all
.PHONY: all clean fclean re
