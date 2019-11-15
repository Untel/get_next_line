SRCS_DIR			= .
SRCS_FILES			= get_next_line.c
SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

INCLUDES			= -I.

CFLAGS				= -Werror -Wextra -Wall $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
CFLAGS				= -Werror -Wextra -Wall $(INCLUDES)
CC					= clang
AR					= ar rc
RM					= rm -f
NAME				= libgnl.a

all:				$(OBJS) get_next_line.h
					$(AR) $(NAME) $(OBJS)

clean:
					$(RM) $(OBJS)
fclean:
					$(RM) $(OBJS)
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re