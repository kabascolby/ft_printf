# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/27 18:43:13 by lkaba             #+#    #+#              #
#    Updated: 2018/03/28 23:05:56 by lkaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
FILES = $(wildcard *.c)
OFILES = $(patsubst %.c, %.o, $(FILES))
LIBFT = libft.a

all: $(NAME)


$(NAME): $(LIBFT) $(OFILES)
	@ar rc $(NAME) $(OFILES) $(wildcard libft/*.o)
	@ranlib $(NAME)

$(LIBFT): force
	@make -C libft

%.o: %.c ft_printf.h
	@echo compiling $<
	@gcc $(FLAGS) -c $<

force:
	@true

cd clean:
	@/bin/rm -f $(FILES:.c=.o)
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft

re: fclean all
