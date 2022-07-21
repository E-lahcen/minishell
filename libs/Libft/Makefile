ANSI_RESET			:= \\033[0m
ANSI_BOLD			:= \\033[2m
ANSI_BOLD_RESET		:= \\033[22m
ANSI_ULINE			:= \\033[4m
ANSI_ULINE_RESET	:= \\033[24m
ANSI_ITALIC			:= \\033[3m
ANSI_ITALIC_RESET	:= \\033[23m
ANSI_RED	:= \\033[38;5;1m
ANSI_WHITE	:= \\033[38;5;15m
ANSI_YELLOW	:= \\033[38;5;3m
ANSI_GREEN	:= \\033[38;5;2m
ANSI_ORANGE	:= \\033[38;5;208m
ANSI_GOLD	:= \\033[38;5;214m
ANSI_BLUE	:= \\033[38;5;4m
ANSI_CYAN	:= \\033[38;5;44m
ANSI_ERASE	:= \\033[2K
ANSI_MOVE	:= \\033[0G

CCW			:= cc -Wall -Wextra -Werror -I../../includes
LIB			:= libft.a
SRCS		:= ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isdigit_z.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_free.c \
	ft_isvalidvar.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c
SRCS_BONUS	:= ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c\
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstsize_bonus.c
OBJS		:= $(SRCS:%.c=bin/%.o)
OBJS_BONUS	:= $(SRCS_BONUS:%.c=bin/%.o)

all : $(LIB)

$(LIB) : bin $(OBJS)

bonus : bin $(OBJS_BONUS)

$(OBJS) $(OBJS_BONUS) :
	@$(CCW) -c $(@:bin/%.o=%.c) -o $@
	@ar -rcs $(LIB) $@

bin :
	@mkdir bin

clean :
	@rm -rf bin

fclean :
	@rm -f $(LIB)

re : fclean all bonus

.PHONY : all bonus clean fclean re
