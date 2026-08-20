NAME    := PmergeMe
SRCS    := main.cpp PmergeMe.cpp
OBJS    = $(SRCS:.cpp=.o)
CC      = c++ -Wall -Wextra -Werror -std=c++98
RM      = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "$(NAME) compiled."

%.o: %.cpp
	@$(CC) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
