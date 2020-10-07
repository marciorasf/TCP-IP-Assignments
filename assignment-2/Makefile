all: client_tcp server_tcp client_udp server_udp

client_tcp: 
	g++ -Wall client_tcp.c test.c -o client_tcp.out

server_tcp:
	g++ -Wall server_tcp.c -o server_tcp.out

client_udp: 
	g++ -Wall client_udp.c test.c -o client_udp.out

server_udp:
	g++ -Wall server_udp.c -o server_udp.out

generate_tests:
	make 
	gnome-terminal -x sh -c "./server_tcp.out"
	gnome-terminal -x sh -c "./client_tcp.out ''"
	gnome-terminal -x sh -c "./server_udp.out"
	gnome-terminal -x sh -c "./client_udp.out ''"