NAME	=	philo
CC		= 	gcc
CFLAGS	=	-g -I includes -Wall -Wextra -Werror

SRCS = $(wildcard src/*.c)

OBJDIR	=	obj
OBJS	=	$(SRCS:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

