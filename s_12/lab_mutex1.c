#include <linux/module.h>
#include <linux/init.h>

DEFINE_MUTEX(my_mutex);
EXPORT_SYMBOL(my_mutex);

static int __init my_init(void)
{
	pr_info("Intit mutex: module loaded %s 0x%p\n", KBUILD_MODNAME, my_init);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Bye: module %s unloaded from 0x%p\n", KBUILD_MODNAME, my_exit);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


