#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/stack_check.h>

void kernel_main(void)
{
	terminal_initialize();
	printf("Hello, kernel World!\n");
}
