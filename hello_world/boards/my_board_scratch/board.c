#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

void board_early_init_hook(void)
{
	/* early hardware setup */
}

static int my_board_init(void)
{
	printk("Board Initialized\n");
	return 0;
}

SYS_INIT(my_board_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
