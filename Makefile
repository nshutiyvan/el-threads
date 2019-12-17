
CR="arm-linux-gcc"
CC="gcc"
FLAGS="-Wall"

OBJS=sync.o

.PHONY:clean all
all: $(OBJS)
	 $(CC) $(FLAGS) -o Sync sync.o -lrt -pthread 

sync.o:sync.c
			$(CC) $(FLAGS) -c -o sync.o  sync.c 


clean:
	rm -rf Sync sync.o
