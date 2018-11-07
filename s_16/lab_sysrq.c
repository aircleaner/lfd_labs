#include <linux/module.h>
#include <linux/init.h>
#include <linux/sysrq.h>

static void my_sysrq_handler(int key)
{
	pr_info("Hello from func %s, key pressed: %c\n", __func__, key);
}

static struct sysrq_key_op my_sysrq = {
	.handler = my_sysrq_handler,
	.help_msg = "Test press X",
	.action_msg = "test message",
};

static int __init my_init(void)
{
	int res = register_sysrq_key('x', &my_sysrq); 
	if (res == 0)
		pr_info("sysrq registered\n");
	else
		pr_info("failed register sysrq\n");
	return res;
}

static void __exit my_exit(void)
{
	int res = unregister_sysrq_key('x', &my_sysrq);
	if (res == 0)
		pr_info("sysrq unregister\n");
	else
		pr_info("failed unregister\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


