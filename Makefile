# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 12:37:52 by zwina             #+#    #+#              #
#    Updated: 2022/06/15 12:33:28 by lelhlami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG		:= -fsanitize=address -g
CCWI		:= gcc -Wall -Wextra -Werror -Iincludes
BREWFGI		:= -I ~/Downloads/homebrew/opt/readline/include
BREWFGL		:= -L ~/Downloads/homebrew/opt/readline/lib
EXFGS		:= -lreadline $(BREWFGL)
NAME		:= minishell
# directories
SRCSDIR		:= srcs
OBJSDIR		:= objs
EXECDIR		:= execution
PARSDIR		:= parsing
PARCMDDIR	:= parser_cmdline
PARPIPDIR	:= parser_pipeline
PARLISDIR	:= parser_listline
# libf
LIBFTDIR	:= ./libs/Libft
LIBFT		:= $(LIBFTDIR)/libft.a
# sources
CEXEC		:=		executor.c \
					paths.c
CPARCMD		:=			parser_cmdline.c \
						parser_word.c \
						expand_args.c \
						expand_astrisk.c \
						get_elements.c \
						expand_dollars.c \
						expand_quotes.c \
						expanding_relinking.c \
						set_stats.c \
						set_heredoc.c \
						fill_cmdline.c
CPARPIP		:=			parser_pipeline.c
CPARLIS		:=			parser_listline.c \
						free_listline.c
CPARS		:=		parser.c \
					error_pre_parsing.c \
					error_parenthesis.c \
					error_unexpected.c \
					$(foreach F,$(CPARCMD),$(PARCMDDIR)/$(F)) \
					$(foreach F,$(CPARPIP),$(PARPIPDIR)/$(F)) \
					$(foreach F,$(CPARLIS),$(PARLISDIR)/$(F))
CFILES		:=	minishell.c \
				signals.c \
				PRINTING.c \
				errors.c \
				$(foreach F,$(CEXEC),$(EXECDIR)/$(F)) \
				$(foreach F,$(CPARS),$(PARSDIR)/$(F))
SRCS		:= $(foreach F,$(CFILES),$(SRCSDIR)/$(F))
# objects
OBJS		:= $(patsubst $(SRCSDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))

all : $(NAME)

debug : CCWI += $(DEBUG)
debug : all

$(NAME) : $(LIBFT) $(OBJSDIR) $(OBJS) 
	$(CCWI) $(EXFGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS) : $(OBJSDIR)/%.o : $(SRCSDIR)/%.c
	$(CCWI) -c $< -o $@ $(BREWFGI)

$(OBJSDIR) :
	@mkdir $(OBJSDIR)
	@mkdir $(OBJSDIR)/$(EXECDIR)
	@mkdir $(OBJSDIR)/$(PARSDIR)
	@mkdir $(OBJSDIR)/$(PARSDIR)/$(PARCMDDIR)
	@mkdir $(OBJSDIR)/$(PARSDIR)/$(PARPIPDIR)
	@mkdir $(OBJSDIR)/$(PARSDIR)/$(PARLISDIR)

$(LIBFT) :
	@make all bonus -C $(LIBFTDIR)

clean :
	@make clean -C $(LIBFTDIR)
	rm -rf $(OBJSDIR)

fclean : clean
	@make fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re : fclean all

.PHONY : clean
