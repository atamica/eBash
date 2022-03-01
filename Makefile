NAME = minishell

SRC = srcs/

OSY = $(shell uname)

BUILTINS = cd.c echo.c pwd.c manager.c env.c env1.c export.c unset.c exit.c

REDIR = rd.c rd1.c

CFGNL = get_next_line.c get_next_line_utils.c

X = start.c

CF_BONUS = star.c

CFTST = parser.c parser1.c utils.c utils1.c utils2.c utils3.c free.c err.c \
	err1.c init.c is.c is1.c run.c replace.c replace1.c signals.c \
	history.c close.c heredoc.c \
	$(addprefix builtins/, $(BUILTINS)) \
	$(addprefix redirections/, $(REDIR))

GNLPH = gnl/
GNL = $(addprefix $(GNLPH), $(CFGNL))
	
CF1 = $X $(CFTST)

#CFTST = $(subst $X, , $(CF1))

LIBDIR = libft/

LIBFT = $(LIBDIR)libft.a

HDIR = ./includes

HDF = $(NAME).h $(NAME)_std_lib.h $(NAME)_consts.h $(NAME)_structs.h

HDRS = $(addprefix $(HDIR)/, $(HDF)) $(LIBDIR)libft.h $(GNLPH)get_next_line.h

ifneq ($(OSY), Linux)
CC = gcc
INCLUD = -I $(HDIR) -I $(LIBDIR) -I $(GNLPH) -I ~/.brew/Cellar/readline/8.1.1/include 
LIBS = -L $(LIBDIR) $(LIBFT) -lreadline  -L ~/.brew/Cellar/readline/8.1.1/lib/
else
CC = gcc # clang
INCLUD = -I $(HDIR) -I $(LIBDIR) -I /usr/local/include -I $(GNLPH)
LIBS = -L $(LIBDIR) -lft -lreadline
endif

ifeq ($(BON), 1)
	CF1 += $(CF_BONUS)
	D = -D BONUS=1
else
	D = -D BONUS=0
endif

CF=$(addprefix $(SRC), $(CF1)) $(GNL)

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

all: $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(FL) -c $< -o $@ $D

$(NAME): $(OF) $(HDRS) $(LIBFT)
	$(CC) -o $@ $(FL) $(OF) $(LIBS) $(DEPFL) $D

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
	norminette --cfile $(CF)
	norminette --hfile $(HDRS)
	$(MAKE) norm -C $(LIBDIR)	

run: $(NAME)
	./$(NAME)

runb: bonus
	./$(NAME)

tst: $(HDRS) $(LIBFT)
	gcc -I includes -I gnl -I libft -o tst srcs/tst/tst_star.c \
	$(addprefix $(SRC), $(CF_BONUS)) \
	$(addprefix $(SRC), $(CFTST)) $(GNL) $(LIBS); ./tst

tst_pipe_split: $(HDRS) $(LIBFT)
#	gcc -I includes -I libft -o tst_pipe_split srcs/get_spec_char.c tmp/test_parser_cmd_set.c srcs/signals.c libft/libft.a; ./tst_pipe_split

val: $(NAME)
	clear
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(NAME)

valb: bonus $(NAME)
	clear
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# --track-origins=yes --leak-check=full -s ARG=$(ARG);

dd:
	clear
	@echo $(CFTST)
	@echo ---
	@echo $(CF1)
	@echo $(CF_BONUS)
	@echo $(MAKE_TERMOUT)

.PHONY: all bonus clean dd fclean norm re run runb tst val valb tst_pipe_split

# -L /Users/atamica/./brew/Cellar/readline/8.1/lib -I /Users/atamica/./brew/Cellar/readline/8.1/include
