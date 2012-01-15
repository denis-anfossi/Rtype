
CC 	= 	g++ -o

NAME 	=	R-Type-server

SOCKET	=	Socket/
THREAD	=	Thread/
DLL	=	DLL/

SRC 	= 	main.cpp		\
		Command.cpp		\
		Game.cpp		\
		Player.cpp		\
		Server.cpp		\
		ThreadPool_.cpp		\
		$(SOCKET)UnixSocket.cpp	\
		$(SOCKET)WinSocket.cpp	\
		$(THREAD)UnixMutex.cpp	\
		$(THREAD)WinMutex.cpp	\
		$(THREAD)UnixThread.cpp	\
		$(THREAD)WinThread.cpp	\
		$(DLL)LinuxDynLib.cpp	\
		$(DLL)WindowsDynLib.cpp	\

LIB     =       -lpthread -ldl

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
