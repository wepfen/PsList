NAME    =   pslist.exe
SRCS    =   $(wildcard *.c)
OBJS    =   $(SRCS:.c=.obj)

CC      =   cl.exe

CFLAGS  =   /W3 /EHsc


%.obj: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) /c $< /Fo$@
	
# Linking
$(NAME): $(OBJS)
	@echo "Linking..."
	@$(CC) /Fe$(NAME) $(OBJS)
	@echo "'$(NAME)' has been created"

all:    $(NAME)

clean:
	@del $(OBJS)
	@echo "All '.obj' files are now cleared"

fclean: clean
	@del $(NAME)
	@echo "'$(NAME)' and all '.obj' files have been cleared"

re:     fclean all

.PHONY: all clean fclean re