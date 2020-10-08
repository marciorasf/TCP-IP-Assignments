#define TESTS_PER_SIZE 3
#define MESSAGES_PER_TEST 100000
#define MESSAGE_MAX_SIZE 32768

extern void run_test_a(int sock, struct sockaddr_in *server_addr,
                       char *filename);

extern void run_test_b(int sock, struct sockaddr_in *server_addr,
                       char *filename);
