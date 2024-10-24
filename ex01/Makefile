CXX				= c++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 #-fsanitize=address
RM				= rm -fr
INC				= RPN.hpp
NAME			= RPN

SOURCES			= main.cpp RPN.cpp

SOURCES_O		= $(SOURCES:.cpp=.o)

all:			$(NAME)

$(NAME):	$(SOURCES)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $(NAME)

clean:
	@$(RM) $(SOURCES_O)

fclean:			clean
	@$(RM) $(NAME)

re:				fclean $(NAME)

x:
	clear
	@$(RM) $(SOURCES_O)
	@$(RM) $(NAME)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $(NAME)
	@./$(NAME)

.PHONY:			all clean fclean re x