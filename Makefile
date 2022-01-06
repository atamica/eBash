NAME = minishell

SRC = srcs/

all: $(NAME)

OSY = $(shell uname)

BUILTINS = cd.c echo.c pwd.c manager.c env.c env1.c export.c unset.c exit.c

REDIR = rd.c rd1.c

CFGNL = get_next_line.c get_next_line_utils.c

#get_spec_char.c
CF1 = start.c par.c parser.c utils.c utils1.c utils2.c free.c err.c find.c \
	init.c is.c is1.c run.c run1.c run2.c signals.c get_spec_char.c \
	get_spec_old.c \
	$(addprefix builtins/, $(BUILTINS)) \
	$(addprefix redirections/, $(REDIR)) \
	$(addprefix ../gnl/, $(CFGNL)) \
	history.c

CF2 = 

CFTST = par.c parser.c utils.c utils1.c utils2.c free.c err.c find.c \
	init.c is.c is1.c run.c run1.c run2.c signals.c get_spec_char.c \
	get_spec_old.c \
	$(addprefix builtins/, $(BUILTINS)) \
	$(addprefix redirections/, $(REDIR)) \
	$(addprefix ../gnl/, $(CFGNL)) \
	history.c

HDIR = ./includes

HDR = $(HDIR)/$(NAME).h

LIBDIR = libft/

LIBFT = $(LIBDIR)libft.a

ifneq ($(OSY), Linux)
CC = gcc
INCLUD = -I $(HDIR) -I $(LIBDIR) -I gnl/ -I ~/.brew/Cellar/readline/8.1.1/include 
LIBS = -L $(LIBDIR) $(LIBFT) -lreadline  -L ~/.brew/Cellar/readline/8.1.1/lib/
else
CC = gcc # clang
INCLUD = -I $(HDIR) -I $(LIBDIR) -I /usr/local/include -I ./gnl/
LIBS = -L $(LIBDIR) -lft -lreadline
endif

ifeq ($(BON), 1)
	CF=$(addprefix $(SRC)bonus/, $(CF2))
	D = -D BONUS=1
else
	CF=$(addprefix $(SRC), $(CF1))
	D = -D BONUS=0
endif

OF1 = $(CF1:.c=.o)
OF2 = $(CF2:.c=.o)

OF = $(CF:.c=.o)
DF = $(CF:.c=.d)
#OFGNL = $(CFGNL:.c=.o)

DEPFL = -MMD -MF $(@:.o=.d)

-include $(DF)

ifeq ($(OSY), Linux)
	D += -D OS=1
else
	D += -D OS=2
endif

FL = -Wall -Wextra -Werror $(INCLUD) -g # -O2

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
	norminette -o $(addprefix $(SRC), $(CF1)) \
	$(addprefix $(SRC)bonus/, $(CF2)) \
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
	gcc -I includes -I gnl -I libft -o tst srcs/tst_del_sp.c \
	$(addprefix $(SRC), $(CFTST)) $(LIBS); ./tst

tst_pipe_split: $(HDR) $(LIBFT)
#	gcc -I includes -I libft -o tst_pipe_split srcs/get_spec_char.c tmp/test_parser_cmd_set.c srcs/signals.c libft/libft.a; ./tst_pipe_split

val: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(NAME)

valb: bonus $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# --track-origins=yes --leak-check=full -s ARG=$(ARG); 

.PHONY: all bonus clean fclean norm re run runb tst val valb tst_pipe_split

# -L /Users/atamica/./brew/Cellar/readline/8.1/lib -I /Users/atamica/./brew/Cellar/readline/8.1/include
