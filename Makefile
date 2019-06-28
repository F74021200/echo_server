CC = gcc
CLIENT_OBJ = echoclient.o
SERVER_OBJ = echoserver.o


%.o: %.c
	$(CC) -c -o $@ $<

all: client server

client: $(CLIENT_OBJ)
	$(CC) -o client $(CLIENT_OBJ)
server: $(SERVER_OBJ)
	$(CC) -o server $(SERVER_OBJ)

.PHONY: clean
clean:
	-rm *.o client server
