all: client server

client: 
	g++ -Wall -w client.c test.c -o client.out

server:
	g++ -Wall server.c -o server.out

run_local_tests:
	make
	gnome-terminal -x sh -c "./server.out"
	gnome-terminal -x sh -c "./client.out '10.0.0.12'"

clean:
	rm -rf -f images *.csv *.out