#include <linux/module.h>
#include <linux/init.h>

void module1_hello(void);

static int __init my_init(void)
{
	module1_hello();
	// Why can i not put the function call after the print?
	pr_info("Hello: module loaded lab_module2 at 0x%p\n", my_init);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Bye: module lab_module2 unloaded from 0x%p\n", my_exit);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


