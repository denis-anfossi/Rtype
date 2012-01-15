
NAME	=	CreateMonsterFirstTypeDLL.so

SRC	=	MonsterFirstType.cpp	\

OBJ	=	$(SRC:.cpp=.o)

LDFLAGS		= -ldl

RM	=	rm -rf

all	:
		g++ -c -fpic $(SRC) -std=c++0x
		g++ -shared -o $(NAME) $(OBJ)

clean	:
		$(RM) *~

fclean	:	clean
		$(RM) $(NAME) $(OBJ)

re	:	fclean all

.PHONY	:	all clean fclean re
