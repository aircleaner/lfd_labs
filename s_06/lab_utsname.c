#include <linux/module.h>
#include <linux/init.h>
#include <linux/utsname.h>

static int __init my_init(void)
{
	struct new_utsname *utsname = init_utsname();
	pr_info("Hello: module loaded lab_utsname 0x%p\n", my_init);

	//struct new_utsname {
	//char sysname[__NEW_UTS_LEN + 1];
	//char nodename[__NEW_UTS_LEN + 1];
	//char release[__NEW_UTS_LEN + 1];
	//char version[__NEW_UTS_LEN + 1];
	//char machine[__NEW_UTS_LEN + 1];
	//char domainname[__NEW_UTS_LEN + 1];
	pr_info("SYSNAME: %s, nodename %s, release: %s, version: %s, machine: %s, domainname: %s\n", 
			utsname->sysname, utsname->nodename, utsname->release, 
			utsname->version, utsname->machine, utsname->domainname);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Bye: module lab_utsname unloaded from 0x%p\n", my_exit);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


