#include "athrill_syscall.h"
#include "test_reg.h"
#include "test_serial.h"
#include "Socket/TCPSocketConnection.h"

unsigned char stack_data[STACK_SIZE] __attribute__ ((section(".bss_noclr")));
sys_addr athrill_device_func_call __attribute__ ((section(".athrill_device_section")));

TCPSocketConnection *sock_conn;

int main(void)
{
	char buffer[256];
	sock_conn = new TCPSocketConnection();

	(void)sock_conn->connect("127.0.0.1", 50005);

	sock_conn->send("This is a test data\n", sizeof("This is a test data\n"));

	sock_conn->receive(buffer, sizeof(buffer));
	test_print(buffer);
	
	sock_conn->close(true);

	delete sock_conn;
	return 0;
}
