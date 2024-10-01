NAME	=	philo
CC		= 	gcc
CFLAGS	=	-g -I includes 

SRCS = $(wildcard src/*.c)

##LIBFT	=	$(wildcard libft/*.c)

OBJDIR	=	obj
OBJS	=	$(SRCS:src/%.c=$(OBJDIR)/%.o) ##$(LIBFT:libft/%.c=$(OBJDIR)/libft_%.o)

all: $(NAME) ##$(LIBFT) 

##$(LIBFT):
##	$(MAKE) -C libft

$(NAME): $(OBJS) ##$(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

##$(OBJDIR)/libft_%.o: libft/%.c
##	@mkdir -p $(OBJDIR)
##	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re

