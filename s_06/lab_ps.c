#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int __init my_init(void)
{
	struct task_struct *p;
	pr_info("Hello: module loaded lab_ps at 0x%p\n", my_init);
	for_each_process(p)
	{
		// Process ID
		pr_info("PID: %d, state: %ld, cmd: %s", p->pid, p->state, p->comm); 
	}	
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Bye: module lab_ps unloaded from 0x%p\n", my_exit);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


