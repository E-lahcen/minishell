DEBUG		:= -fsanitize=address -g
CCWI		:= gcc -Wall -Wextra -Werror -Iincludes
EXFGS		:= -lreadline
NAME		:= minishell
# directories
SRCSDIR		:= srcs
OBJSDIR		:= objs
EXECDIR		:= execution
PARSDIR		:= parsing
PARCMDDIR	:= parser_cmdline
PARPIPDIR	:= parser_pipeline
PARLISDIR	:= parser_listline
# libft
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
					error_parsing.c \
					$(foreach F,$(CPARCMD),$(PARCMDDIR)/$(F)) \
					$(foreach F,$(CPARPIP),$(PARPIPDIR)/$(F)) \
					$(foreach F,$(CPARLIS),$(PARLISDIR)/$(F))
CFILES		:=	minishell.c \
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
	$(CCWI) -c $< -o $@

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