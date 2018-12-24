#include "athrill_syscall.h"
#include "test_reg.h"


unsigned char stack_data[STACK_SIZE] __attribute__ ((section(".bss_noclr")));
sys_addr athrill_device_func_call __attribute__ ((section(".athrill_device_section")));

int main(void)
{
	return 0;
}
