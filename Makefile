CC     = cc
CFLAGS = -Wall -Werror -Wextra -g 
LDFLAGS = -lreadline -lncurses

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

D_TOK = lexical_analyser 
D_SYN = syntax_error 

SRCS = main.c \
			utiles/track_alloc_free.c \
			utiles/tools.c \
			lexical_analyser/main_token.c \
			syntax_analyser/syntax_analyser.c \
			expanding_variables/expander.c  \
			lexical_analyser/tokenizer_helper.c \
			syntax_analyser/sa_helper.c \
			expanding_variables/expander_helper.c \
			fin_parse/filling.c \
			builtins/dup.c  \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c  \
			builtins/ft_export.c \
			builtins/ft_exit.c  \
			builtins/ft_pwd.c \
			parsing/parsing.c \
			get_env/get_env.c \
			builtins/ft_unset.c \
			execution/execution.c \
			
OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
