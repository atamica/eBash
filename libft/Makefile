# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atamica <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/16 13:35:40 by atamica           #+#    #+#              #
#    Updated: 2020/11/17 18:00:39 by atamica          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SCF = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
     ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
     ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c\
     ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
     ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
     ft_strnstr.c ft_strncmp.c ft_strrchr.c ft_strtrim.c ft_substr.c \
     ft_tolower.c ft_toupper.c

BCF = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
      ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

MCF = ft_isalsp_bonus.c

HDR = libft.h

ifdef BONUS
		CF=$(SCF) $(BCF) $(MCF)
else
		CF=$(SCF) $(MCF)
endif

OF = $(CF:.c=.o)

FL = -Wall -Wextra -Werror -I.

CC = gcc

.PHONY: all bonus clean fclean re dd so sobonus

all: $(NAME)

$(NAME): $(OF) $(HDR)
	ar rcs $(NAME) $?

%.o: %.c $(HDR)
	$(CC) $(FL) -c $< -o $@

bonus:
	$(MAKE) BONUS=1 all

clean:
	rm -f $(OF) $(BCF:.c=.o) $(MCF:.c=.o)

fclean: clean
	rm -f $(NAME) $(NAME:.a=.so)

re: fclean all

dd:
	echo $(CF)
	echo $(BCF)
