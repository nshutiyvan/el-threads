
CR="arm-linux-gcc"
CC="gcc"
FLAGS="-Wall"

OBJS= TCPEchoClient.o TCPEchoServer.o Auxiliary.o AcceptTCPConnection.o\
	CreateTCPServerSocket.o	CreateTCPClientSocket.o	HandleTCPClient.o

.PHONY:clean all
all: $(OBJS)
	 $(CC) $(FLAGS) -o TCPEchoServer Auxiliary.o AcceptTCPConnection.o CreateTCPServerSocket.o HandleTCPClient.o TCPEchoServer.o -lrt 
	 $(CC) $(FLAGS) -o TCPEchoClient Auxiliary.o CreateTCPClientSocket.o TCPEchoClient.o -lrt

TCPEchoServer.o:TCPEchoServer.c Auxiliary.h AcceptTCPConnection.h CreateTCPServerSocket.h HandleTCPClient.h
				$(CC) $(FLAGS) -c -o TCPEchoServer.o  TCPEchoServer.c

TCPEchoClient.o:TCPEchoClient.c Auxiliary.h CreateTCPClientSocket.h
				$(CC) $(FLAGS) -c -o TCPEchoClient.o  TCPEchoClient.c
				
Auxiliary.o:Auxiliary.c Auxiliary.h
			$(CC) $(FLAGS) -c -o Auxiliary.o  Auxiliary.c

AcceptTCPConnection.o:AcceptTCPConnection.c Auxiliary.h
			$(CC) $(FLAGS) -c -o AcceptTCPConnection.o  AcceptTCPConnection.c

CreateTCPServerSocket.o:CreateTCPServerSocket.c CreateTCPServerSocket.h	Auxiliary.h
			$(CC) $(FLAGS) -c -o CreateTCPServerSocket.o  CreateTCPServerSocket.c 

CreateTCPClientSocket.o:CreateTCPClientSocket.c	Auxiliary.h	CreateTCPClientSocket.h
			$(CC) $(FLAGS) -c -o CreateTCPClientSocket.o  CreateTCPClientSocket.c 

HandleTCPClient.o:HandleTCPClient.c Auxiliary.h HandleTCPClient.h
			$(CC) $(FLAGS) -c -o HandleTCPClient.o  HandleTCPClient.c
clean:
	rm -rf AcceptTCPConnection.o Auxiliary.o CreateTCPClientSocket.o \
	AcceptTCPConnection.o CreateTCPServerSocket.o getaddrinfo.o \
	 HandleTCPClient.o TCPEchoClient.o TCPEchoServer-Fork.o \
	 TCPEchoServer.o TCPEchoServer-Thread.o TCPEchoClient \
	  TCPEchoServer-Fork TCPEchoServer TCPEchoServer-Thread
