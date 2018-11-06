#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int __init my_init(void)
{
	struct task_struct *p, *t;
	pr_info("Hello: module loaded lab_ps_thread at 0x%p\n", my_init);
	for_each_process_thread(p, t)
	{
		// Process ID
		pr_info("TGID: %d, PID: %d, state: %ld, cmd: %s", 
				t->tgid, t->pid, t->state, t->comm); 
	}	
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Bye: module lab_ps_thread unloaded from 0x%p\n", my_exit);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


