CC = gcc
CLIENT_OBJ = echoclient.o
SERVER_OBJ = echoserver.o
MUL_P_SERVER = mul_p_server.o


%.o: %.c
	$(CC) -c -o $@ $<

all: client server mul_p_server

client: $(CLIENT_OBJ)
	$(CC) -o client $(CLIENT_OBJ)
server: $(SERVER_OBJ)
	$(CC) -o server $(SERVER_OBJ)
mul_p_server: $(MUL_P_SERVER)
	$(CC) -o mul_p_server $(MUL_P_SERVER)

.PHONY: clean
clean:
	-rm *.o client server mul_p_server
