CC = gcc
CLIENT_OBJ = echoclient.o
SERVER_OBJ = echoserver.o
MUL_P_SERVER = mul_p_server.o
MUL_T_SERVER = mul_t_server.o

%.o: %.c
	$(CC) -c -o $@ $<

all: client server mul_p_server mul_t_server

client: $(CLIENT_OBJ)
	$(CC) -o client $(CLIENT_OBJ)
server: $(SERVER_OBJ)
	$(CC) -o server $(SERVER_OBJ)
mul_p_server: $(MUL_P_SERVER)
	$(CC) -o mul_p_server $(MUL_P_SERVER)
mul_t_server: $(MUL_T_SERVER)
	$(CC) -o mul_t_server $(MUL_T_SERVER) -lpthread

.PHONY: clean
clean:
	-rm *.o client server mul_p_server mul_t_server
