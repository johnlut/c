FLAGS=-Wall -std=gnu99

all: server client

client: rcopy_client.c hash_functions.c
	gcc $(FLAGS) -DSECRET=50000 -o client rcopy_client.c hash_functions.c

server: rcopy_server.c hash_functions.c  
	gcc $(FLAGS) -DSECRET=50000 -o server rcopy_server.c hash_functions.c 

clean:
	-rm -f server
	-rm -f client
	-rm -f *.o
