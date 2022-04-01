# common
C = gcc -Wall -Wextra -Wpedantic -fsanitize=address,undefined
# compile-only args
CO = -c

S = src/
O = obj/

all: client server

client: $(O)client.o
	$(C) $(O)client.o -o client

$(O)client.o: $(S)client.c
	$(C) $(CO) $(S)client.c -o $(O)client.o

server: $(O)server.o
	$(C) $(O)server.o -o server

$(O)server.o: $(S)server.c
	$(C) $(CO) $(S)server.c -o $(O)server.o

clean:
	rm $(O)*.o client server
