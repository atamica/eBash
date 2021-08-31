NAME = minishell

all: $(NAME)

OSY = $(shell uname)

CF1 = 

CF2 = 

HDIR = ./includes

HDR = $(HDIR)/$(NAME).h

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

INCLUD = -I $(HDIR)

ifeq ($(OSY), Linux)
	D += -D OS=1
else
	D += -D OS=2
endif

FL = -Wall -Wextra -Werror $(INCLUD) -g # -O2

CC = gcc #clang

%.o: %.c
	$(CC) $(FL) -c $< -o $@ $(DEPFL) $D

$(NAME): $(OF) $(HDR)
	$(CC) -o $@ $(FL) $(OF) $(DEPFL) $D

# $? 

bonus:
	$(MAKE) BON=1 all

clean:
	rm -rf $(OF)
	rm -rf $(DF)
	rm -rf $(NAME).d

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette -v
	norminette -o $(addprefix srcs/, $(CF1)) \
	$(addprefix srcs/bonus/, $(CF2)) \
	$(HDIR)/*.h

CMD1="cat -e"
CMD2="grep f"
CMD3="wc -wlc"
FILE1=file1
FILE2=file2
CMD="< $(FILE1) $(CMD1) | $(CMD2) > $(FILE2)"
CMDB="< $(FILE1) $(CMD1) | $(CMD2) | $(CMD3) > $(FILE2)"
run: $(NAME)
	./$(NAME) $(FILE1) $(CMD1) $(CMD2) $(FILE2)

runb: bonus
	./$(NAME) $(FILE1) $(CMD1) $(CMD2) $(CMD3) $(FILE2)

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(FILE1) $(CMD1) $(CMD2) $(FILE2)

valb: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(FILE1) $(CMD1) $(CMD2) $(CMD3) $(FILE2)

# --track-origins=yes --leak-check=full -s ARG=$(ARG); 

.PHONY: all bonus clean fclean norm re run runb val valb