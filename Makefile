SHELL = /bin/sh

NAME_FILE = avm

FLAGS = -Wall -Wextra -Werror -std=c++20

SRCS = CodeAnalyzer.cpp ErrorManager.cpp Lexer.cpp main.cpp OperandCreator.cpp Parser.cpp Vm.cpp

OBJS = $(SRCS:.cpp=.o)

HEADER_PATH = ./includes/
HEADER_FILES = CodeAnalyzer.h Error.h ErrorManager.h IOperand.h Lexer.h Operand.h OperandCreator.h Parser.h Vm.h
HEADERS = $(addprefix $(HEADER_PATH),$(HEADER_FILES))

vpath %.cpp ./srcs
vpath %.h ./includes

all: $(NAME_FILE)

$(NAME_FILE): $(OBJS)
	@g++ -o $(NAME_FILE) $(OBJS)

$(OBJS): %.o:%.cpp $(HEADERS)
	@g++ -c $< -I$(HEADER_PATH) $(FLAGS) -o $@

.PHONY: clean fclean re
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME_FILE)

re: fclean all