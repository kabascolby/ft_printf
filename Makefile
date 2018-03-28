# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/27 18:43:13 by lkaba             #+#    #+#              #
#    Updated: 2018/03/27 19:31:52 by lkaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a
FLAGS = -Wall -Wextra -Werror
FILES = $(wildcard *.c)
OFILES = $(patsubst %.c, %.o, $(FILES))
LIBFT = libft.a

all: $(NAME)


$(NAME): $(OFILES)
	@make re -C libft
	@cp libft/libft.a ./$@
	@gcc -c $(FLAGS) $(FILES)
	# @gcc $(FLAGS) $(OFILES) libft/$(LIBFT)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)

# $(LIBFT):
# 	@make -C libft

%.o: %.c
	gcc $(FLAGS) -c $<

clean:
	@/bin/rm -f $(FILES:.c=.o)
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft

re: fclean all
#  @make re -C $(LIBFT)
#     @cp libft/libft.a ./$@
#     @ar rc $@ $(OBJS)
#     @ranlib $@