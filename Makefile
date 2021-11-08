NAME = minishell

all: $(NAME)

OSY = $(shell uname)

BUILTINS = cd.c echo.c pwd.c manager.c env.c env1.c export.c unset.c exit.c

REDIR = rd.c rd1.c

CF1 = start.c par.c parser.c utils.c free.c err.c find.c init.c is.c is1.c \
	get_spec_char.c run.c run1.c signals.c\
	$(addprefix builtins/, $(BUILTINS)) \
	$(addprefix redirections/, $(REDIR))
CF2 = 

HDIR = ./includes

HDR = $(HDIR)/$(NAME).h

LIBDIR = libft/

LIBFT = $(LIBDIR)libft.a



ifneq ($(OSY), Linux)
INCLUD = -I $(HDIR) -I $(LIBDIR) -I ~/.brew/Cellar/readline/8.1.1/include 
LIBS = -L $(LIBDIR) $(LIBFT) -lreadline  -L ~/.brew/Cellar/readline/8.1.1/lib/
else
INCLUD = -I $(HDIR) -I $(LIBDIR) -I /usr/local/include
LIBS = -L $(LIBDIR) -lft -lreadline
endif

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

%.o: %.c $(HDR)
	$(CC) $(FL) -c $< -o $@ $D

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

tst: $(HDR) $(LIBFT)
	gcc -I includes -I libft -o tst srcs/get_spec_char.c tmp/tst_escaped_char.c  libft/libft.a; ./tst

tst_pipe_split: $(HDR) $(LIBFT)
	gcc -I includes -I libft -o tst_pipe_split srcs/get_spec_char.c tmp/test_parser_cmd_set.c srcs/signals.c libft/libft.a; ./tst_pipe_split

val: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(NAME)

valb: bonus $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# --track-origins=yes --leak-check=full -s ARG=$(ARG); 

.PHONY: all bonus clean fclean norm re run runb tst val valb tst_pipe_split

# -L /Users/atamica/./brew/Cellar/readline/8.1/lib -I /Users/atamica/./brew/Cellar/readline/8.1/include
