#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>

extern struct mutex my_mutex;

static int __init my_init(void)
{
	pr_info("Hello: module loaded %s 0x%p\n", KBUILD_MODNAME, my_init);

	mutex_lock(&my_mutex);

	pr_info("Mutex locked from %s\n", KBUILD_MODNAME);
	return 0;
}

static void __exit my_exit(void)
{
	mutex_unlock(&my_mutex);
	pr_info("Bye: module %s unloaded from 0x%p\n", KBUILD_MODNAME, my_exit);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


