# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwina <zwina@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 12:37:52 by zwina             #+#    #+#              #
#    Updated: 2022/06/25 00:06:46 by zwina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ANSI_RESET			:= \\033[0m
ANSI_BOLD			:= \\033[2m
ANSI_BOLD_RESET		:= \\033[22m
ANSI_ULINE			:= \\033[4m
ANSI_ULINE_RESET	:= \\033[24m
ANSI_ITALIC			:= \\033[3m
ANSI_ITALIC_RESET	:= \\033[23m
ANSI_RED		:= \\033[38;5;125m
ANSI_LRED		:= \\033[38;5;196m
ANSI_WHITE		:= \\033[38;5;15m
ANSI_YELLOW		:= \\033[38;5;3m
ANSI_GREEN		:= \\033[38;5;2m
ANSI_ORANGE		:= \\033[38;5;208m
ANSI_LORANGE	:= \\033[38;5;215m
ANSI_GOLD		:= \\033[38;5;214m
ANSI_BLUE		:= \\033[38;5;4m
ANSI_PURPLE		:= \\033[38;5;129m
ANSI_CYAN		:= \\033[38;5;44m

DEBUG		:= -fsanitize=address -g
CCWI		:= gcc -Wall -Wextra -Werror -Iincludes
RDINC		:= -I ~/Downloads/homebrew/opt/readline/include
RDLIB		:= -L ~/Downloads/homebrew/opt/readline/lib -lreadline
NAME		:= minishell
# directories
SRCSDIR		:= srcs
OBJSDIR		:= objs
BUILTSDIR	:= builtins
EXECDIR		:= execution
PARSDIR		:= parsing
PARCMDDIR	:= parser_cmdline
# libf
LIBFTDIR	:= ./libs/Libft
LIBFT		:= $(LIBFTDIR)/libft.a
# sources
CBUILTS		:=		cd.c \
					echo.c \
					env.c \
					exit.c \
					export.c \
					pwd.c \
					unset.c
CEXEC		:=		executor_shelline.c \
					executor_listline.c \
					executor_pipeline.c \
					executor_cmdline.c \
					paths.c \
					set_files.c \
					$(foreach F,$(CBUILTS),$(BUILTSDIR)/$(F))
CPARCMD		:=			parser_cmdline.c \
						parser_word.c \
						expand_args.c \
						expand_astrisk.c \
						get_elements.c \
						expand_dollars.c \
						expand_quotes.c \
						expanding_relinking.c \
						set_stats.c \
						set_heredocs.c \
						fill_heredoc.c \
						cmdline_utils.c
CPARS		:=		parser_shelline.c \
					error_parsing.c \
					error_unexpected.c \
					parser_listline.c \
					free_listline.c \
					parser_pipeline.c \
					$(foreach F,$(CPARCMD),$(PARCMDDIR)/$(F))
CFILES		:=	minishell.c \
				signals.c \
				errors.c \
				$(foreach F,$(CPARS),$(PARSDIR)/$(F)) \
				$(foreach F,$(CEXEC),$(EXECDIR)/$(F))
SRCS		:= $(foreach F,$(CFILES),$(SRCSDIR)/$(F))
# objects
OBJS		:= $(patsubst $(SRCSDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))

all : $(NAME)

bonus : all

debug : CCWI += $(DEBUG)
debug : all

$(NAME) : $(LIBFT) $(OBJSDIR) $(OBJS)
	@$(CCWI) $(RDLIB) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "$(ANSI_GREEN)"
	@printf "███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n"
	@printf "████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n"
	@printf "██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n"
	@printf "██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n"
	@printf "██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\n"
	@printf "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n"
	@printf "$(ANSI_RESET)\\033[38;5;10m"
	@printf "▀█▀ █▀▀ 　 ▒█▀▀█ █▀▀ █▀▀█ █▀▀▄ █░░█\n"
	@printf "▒█░ ▀▀█ 　 ▒█▄▄▀ █▀▀ █▄▄█ █░░█ █▄▄█\n"
	@printf "▄█▄ ▀▀▀ 　 ▒█░▒█ ▀▀▀ ▀░░▀ ▀▀▀░ ▄▄▄█\n"
	@printf "$(ANSI_RESET)"

$(OBJS) : $(OBJSDIR)/%.o : $(SRCSDIR)/%.c
	@$(CCWI) $(RDINC) -c $< -o $@
	@printf "$(ANSI_PURPLE)$(ANSI_ITALIC)"
	@printf "$@ "
	@printf "$(ANSI_GREEN)"
	@printf "[DONE]\n"
	@printf "$(ANSI_RESET)"

$(OBJSDIR) :
	@mkdir $(OBJSDIR)
	@mkdir $(OBJSDIR)/$(EXECDIR)
	@mkdir $(OBJSDIR)/$(EXECDIR)/$(BUILTSDIR)
	@mkdir $(OBJSDIR)/$(PARSDIR)
	@mkdir $(OBJSDIR)/$(PARSDIR)/$(PARCMDDIR)

$(LIBFT) :
	@printf "$(ANSI_ORANGE)"
	@printf "|-------------------|\n"
	@printf "$(ANSI_LORANGE)"
	@printf "  Creating LIBFT ...\n"
	@make all bonus -C $(LIBFTDIR)
	@printf "       [DONE].\n"
	@printf "$(ANSI_ORANGE)"
	@printf "|-------------------|\n"
	@printf "$(ANSI_RESET)"

clean :
	@make clean -C $(LIBFTDIR)
	@rm -rf $(OBJSDIR)
	@printf "$(ANSI_LRED)"
	@printf "|-------------------|\n"
	@printf "  Cleaning OBJS ...\n"
	@printf "       [DONE].\n"
	@printf "|-------------------|\n"
	@printf "$(ANSI_RESET)"

fclean : clean
	@make fclean -C $(LIBFTDIR)
	@rm -rf $(NAME)
	@printf "$(ANSI_RED)"
	@printf "|----------------------|\n"
	@printf "  REMOVE MINISHELL ...\n"
	@printf "         [DONE].\n"
	@printf "|----------------------|\n"
	@printf "$(ANSI_RESET)"

re : fclean all

.PHONY : clean
