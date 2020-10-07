all: client server

client: 
	g++ -Wall -w client.c test.c -o client.out

server:
	g++ -Wall server.c -o server.out

run_tests:
	make
	gnome-terminal -x sh -c "./server.out"
	gnome-terminal -x sh -c "./client.out ''"