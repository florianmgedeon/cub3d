# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:59:11 by jkoupy            #+#    #+#              #
#    Updated: 2024/06/18 15:08:06 by jkoupy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[38;5;196;1m
ORANGE = \033[38;5;208;1m
YELLOW = \033[38;5;226;1m
GREEN = \033[38;5;082;1m
BLUE = \033[38;5;027;1m
INDIGO = \033[38;5;093;1m
VIOLET = \033[38;5;163;1m
WHITE = \033[38;5;231;1m
BROWN = \033[38;5;137;1m
END = \033[0m

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RFLAGS = -lreadline
DEPFLAGS = -MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.d
RM = rm -rf

LIBFT =	library/libft/libft.a
GETNEXTLINE = 	library/get_next_line/getnextline.a

SRCS =	main.c
			
OBJ_DIR = object/
OBJS =  $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.d))

all: $(NAME) 

object/%.o: source/%.c
	@mkdir -p $(dir $@)
	@printf "$(ORANGE). $(END)";
	@$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(NAME): $(LIBFT) $(GETNEXTLINE) $(OBJS) 
	@$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(GETNEXTLINE) -o $(NAME) $(RFLAGS)
	@$(RM) heredocs
	@mkdir heredocs
	@printf "\r$(GREEN)🚀 ./$(NAME)          created                                                                     \n$(END)"

$(LIBFT):
	@make bonus -sC library/libft

$(GETNEXTLINE):
	@printf "$(ORANGE).$(END)"
	@make -sC library/get_next_line

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC library/libft
	@make clean -sC library/get_next_line
	@printf "$(RED)💥 object files\t\tremoved\n$(END)"

fclean: clean
	@make fclean -sC library/libft
	@make fclean -sC library/get_next_line
	@$(RM) $(NAME)
	@$(RM) test
	@$(RM) heredocs
	@printf "$(RED)💥 ./$(NAME) \t\tremoved\n$(END)"

re: _rebuild fclean all

_rebuild:
	@printf "$(ORANGE)🚧 ./$(NAME)\t\trebuild\n$(END)"

nothing:
	@printf "💩$(BROWN) made $(RED)n$(ORANGE)o$(YELLOW)t$(GREEN)h$(BLUE)i$(INDIGO)n$(VIOLET)g\n$(END)"

-include $(DEPS)

.PHONY: all bonus both clean fclean re _rebuild nothing