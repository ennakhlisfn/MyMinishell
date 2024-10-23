NAME=minishell
CFLAGS= -Wall -Wextra -Werror -g3 #-fsanitize=address 
LR = -lreadline

SRC=skip.c expand.c ft_free.c errors.c fill.c main.c parsing.c structs.c strings.c\
hered.c prex/builtins.c prex/builtins1.c prex/builtins2.c prex/getcmd.c\
prex/fexec.c prex/ft_export.c prex/ft_exputil.c prex/ft_pexpo.c prex/utils4.c\
prex/lib.c prex/lib1.c  prex/lib2.c prex/onecom.c prex/operation.c prex/pipe.c\
prex/redire.c prex/utils.c prex/utils1.c prex/utils2.c prex/utils3.c prex/utils5.c\
main1.c check.c fill2.c string2.c prex/utils6.c hered2.c prex/utils7.c
OBJ=$(SRC:.c=.o)

all:$(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $^ $(LR) -o $@ 

%.o: %.c
	cc $(CFLAGS)  $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re : fclean all

.SECONDARY : $(OBJ)
