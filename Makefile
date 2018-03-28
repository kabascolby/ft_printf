# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/27 18:43:13 by lkaba             #+#    #+#              #
#    Updated: 2018/03/27 20:04:20 by lkaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a
FLAGS = -Wall -Wextra -Werror
FILES = *.c
LIBFT = libft.a

all: $(NAME)


$(NAME): $(OFILES)
	@make re -C libft
	@cp libft/libft.a ./$@
	@gcc -c $(FLAGS) $(FILES)
	@ar rc $(NAME) $(FILES:.c=.o)
	@ranlib $(NAME)
clean:
	@/bin/rm -f $(FILES:.c=.o)
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft

re: fclean all
