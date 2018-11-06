#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
	pr_info("Hello: module loaded lab_module1 at 0x%p\n", my_init);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Bye: module lab_module1 unloaded from 0x%p\n", my_exit);
}

static void module1_hello(void)
{
	pr_info("Hello from module 1 function");
}

EXPORT_SYMBOL(module1_hello);

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


