NAME = minishell

all: $(NAME)

OSY = $(shell uname)

CF1 = start.c parser.c utils.c free.c err.c

CF2 = 

HDIR = ./includes

HDR = $(HDIR)/$(NAME).h

LIBDIR = libft/

LIBFT = $(LIBDIR)libft.a

INCLUD = -I $(HDIR) -I $(LIBDIR) -I /usr/local/include

LIBS = -L $(MLXDIR) -lmlx -L $(LIBDIR) -lft -lreadline

ifeq ($(BON), 1)
		CF=$(addprefix srcs/bonus/, $(CF2))
		D = -D BONUS=1
else
		CF=$(addprefix srcs/, $(CF1))
		D = -D BONUS=0
endif

OF1 = $(CF1:.c=.o)
OF2 = $(CF2:.c=.o)

OF = $(CF:.c=.o)
DF = $(CF:.c=.d)

DEPFL = -MMD -MF $(@:.o=.d)

-include $(DF)

ifeq ($(OSY), Linux)
	D += -D OS=1
else
	D += -D OS=2
endif

FL = -Wall -Wextra -Werror $(INCLUD) -g # -O2

CC = gcc #clang

%.o: %.c $(HDR) $(LIBFT)
	$(CC) $(FL) -c $< -o $@ $(LIBS) $(DEPFL) $D

$(NAME): $(OF) $(HDR) $(LIBFT)
	$(CC) -o $@ $(FL) $(OF) $(LIBS) $(DEPFL) $D

# $? 

$(LIBFT):
	$(MAKE) -C $(LIBDIR) bonus

bonus:
	$(MAKE) BON=1 all

clean:
	rm -rf $(OF)
	rm -rf $(DF)
	rm -rf $(NAME).d
	$(MAKE) fclean -C $(LIBDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette -v
	norminette -o $(addprefix srcs/, $(CF1)) \
	$(addprefix srcs/bonus/, $(CF2)) \
	$(HDIR)/*.h \
	$(LIBDIR)


CMD1="cat -e"
CMD2="grep f"
CMD3="wc -wlc"
FILE1=file1
FILE2=file2
CMD="< $(FILE1) $(CMD1) | $(CMD2) > $(FILE2)"
CMDB="< $(FILE1) $(CMD1) | $(CMD2) | $(CMD3) > $(FILE2)"
run: $(NAME)
	./$(NAME)

runb: bonus
	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

valb: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# --track-origins=yes --leak-check=full -s ARG=$(ARG); 

.PHONY: all bonus clean fclean norm re run runb val valb