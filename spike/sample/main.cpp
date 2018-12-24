#include "athrill_syscall.h"
#include "test_reg.h"
#include "test_serial.h"
#include "Socket/TCPSocketConnection.h"
#include "Socket/TCPSocketServer.h"
#include <string.h>

unsigned char stack_data[STACK_SIZE] __attribute__ ((section(".bss_noclr")));
sys_addr athrill_device_func_call __attribute__ ((section(".athrill_device_section")));

TCPSocketConnection *sock_conn;
TCPSocketServer *sock_srv;

unsigned int test_mode  __attribute__ ((section(".bss_noclr")));

int main(void)
{
	char buffer[256];

	test_print("main:enter\n");

	if (test_mode == 0) {
		sock_conn = new TCPSocketConnection();

		(void)sock_conn->connect("127.0.0.1", 50005);

		sock_conn->send((char*)"This is a test data\n", sizeof("This is a test data\n"));

		sock_conn->receive(buffer, sizeof(buffer));
		test_print(buffer);
		test_print("\n");

		sock_conn->close(true);

		delete sock_conn;
	}
	else {
		TCPSocketConnection new_conn;
		sock_srv = new TCPSocketServer();
		sock_srv->bind(50005);
		sock_srv->listen();
		sock_srv->accept(new_conn);

		new_conn.receive(buffer, sizeof(buffer));
		test_print(buffer);
		test_print("\n");

		new_conn.send(buffer, strlen(buffer));
		new_conn.close();

		sock_srv->close(true);
		delete sock_srv;
	}
	return 0;
}
