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
	@printf "$(ANSI_CYAN)$(ANSI_ULINE)libft.a is created with the mandatory part.\n$(ANSI_RESET)"

bonus : bin $(OBJS_BONUS)
	@printf "$(ANSI_CYAN)$(ANSI_ULINE)libft.a is created with the bonus part.\n$(ANSI_RESET)"

$(OBJS) $(OBJS_BONUS) :
	@$(CCW) -c $(@:bin/%.o=%.c) -o $@
	@ar -rcs $(LIB) $@
	@printf "$(ANSI_ITALIC)%s$(ANSI_RESET)\t\t$(ANSI_GREEN)[Done]\n$(ANSI_RESET)" \
		"$(@:bin/%.o=%.c)"

bin :
	@mkdir bin
	@printf "$(ANSI_CYAN)bin directory is created.\n$(ANSI_RESET)"

clean :
	@rm -rf bin
	@printf "$(ANSI_RED)$(ANSI_ITALIC)object files and bin directory are removed.\n$(ANSI_RESET)"

fclean :
	@rm -f $(LIB)
	@printf "$(ANSI_RED)$(ANSI_ULINE)libft.a is removed.\n$(ANSI_RESET)"

re : fclean all bonus

.PHONY : all bonus clean fclean re
