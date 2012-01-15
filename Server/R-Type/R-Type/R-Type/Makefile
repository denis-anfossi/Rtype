
CC 	= 	g++ -o

NAME 	=	R-Type-server

SOCKET	=	Socket/

THREAD	=	Thread/

SRC 	= 	main.cpp		\
		Command.cpp		\
		Game.cpp		\
		Player.cpp		\
		Server.cpp		\
		$(SOCKET)UnixSocket.cpp	\
		$(SOCKET)WinSocket.cpp	\
		$(THREAD)UnixMutex.cpp	\
		$(THREAD)WinMutex.cpp	\
		$(THREAD)UnixThread.cpp	\
		$(THREAD)WinThread.cpp	\

LIB     =       -lpthread

INCLUDE =       -I.

OBJ	=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Wextra

all	:	$(NAME) 

$(NAME)	:	$(OBJ)
		$(CC) $(NAME) $(OBJ) $(CFLAGS) $(INCLUDE)  $(LIB) -std=c++0x

clean	:
		$(RM) *~ \#*\# *core

fclean	:	clean
		$(RM) $(NAME) *.o

re	:	fclean all

.PHONY	:	all clean fclean re
