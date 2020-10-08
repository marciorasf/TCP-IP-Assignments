#define TESTS_PER_SIZE 3  // how many tests are repeated for every message size
#define MESSAGES_PER_TEST 100000  // how many messages are sent on a single test
#define MESSAGE_MAX_SIZE 32768  // defined as 32 kB

void run_test_a(int sock, struct sockaddr_in *server_addr, char *filename);

void run_test_b(int sock, struct sockaddr_in *server_addr, char *filename);
