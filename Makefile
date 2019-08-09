CC = gcc
ECHO_OBJ = echo.o
CLIENT_OBJ = echoclient.o
MUL_P_SERVER = mul_p_server.o
MUL_T_SERVER = mul_t_server.o

%.o: %.c
	$(CC) -c -o $@ $<

all: client mul_p_server mul_t_server

client: $(CLIENT_OBJ) $(ECHO_OBJ)
	$(CC) -o client $(CLIENT_OBJ) $(ECHO_OBJ)
mul_p_server: $(MUL_P_SERVER) $(ECHO_OBJ)
	$(CC) -o mul_p_server $(MUL_P_SERVER) $(ECHO_OBJ)
mul_t_server: $(MUL_T_SERVER) $(ECHO_OBJ)
	$(CC) -o mul_t_server $(MUL_T_SERVER) $(ECHO_OBJ) -lpthread

.PHONY: clean
clean:
	-rm *.o client mul_p_server mul_t_server
