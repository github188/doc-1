OBJECTS := client_main.o server_main.o mainfifo.o mainpopen.o \
mainpipe.o comm.o mainserver.o mainclient.o
TARGETS := client_main server_main mainfifo mainpopen mainpipe \
mainserver mainclient
CFLAGS += -Wall -g

all:  $(TARGETS) $(OBJECTS)

comm.o : comm.c comm.h ../unpipc.h
	$(CC) -c  $^ $(CFLAGS)

client_main : comm.o client_main.o
	$(CC) -o $@ $^  $(CFLAGS)

server_main: comm.o server_main.o
	$(CC) -o $@ $^ $(CFLAGS)

mainfifo: comm.o mainfifo.o
	$(CC) -o $@ $^ $(CFLAGS)

mainpopen: comm.o mainpopen.o
	$(CC) -o $@ $^ $(CFLAGS)

mainpipe: comm.o mainpipe.o
	$(CC) -o $@ $^ $(CFLAGS)

mainserver: comm.o mainserver.o
	$(CC) -o $@ $^ $(CFLAGS)

mainclient: comm.o mainclient.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY : clean
clean :
	rm -rf *.o $(OBJECTS) $(TARGETS)
