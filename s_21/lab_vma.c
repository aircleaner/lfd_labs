#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>

static int pid;
// sudo insmod lab_vma.ko pid=$PID
module_param(pid, int, S_IRUGO);

static int __init my_init(void)
{
	struct task_struct *task;
	struct mm_struct *mm;
	struct vm_area_struct *vma;
	int j = 0;

	pr_info("Hello: module loaded %s 0x%p\n", KBUILD_MODNAME, my_init);
	if (pid == 0)
	{
		task = current;
		pid = current->pid;
	}
	else
	{
		task = pid_task(find_vpid(pid), PIDTYPE_PID);
	}
	if (!task)
	{
		pr_info("Task failed to initialize\n");
		return -1;
	}

	mm = task->mm;
	vma = mm->mmap;
	down_read(&mm->mmap_sem);
	pr_info("Examine values for pid=%d, command=%s\n", pid, task->comm);

	while (vma)
	{
		j++;
		pr_info("VMA: %d, %lx - %lx (%ld bytes)\n", 
				j, vma->vm_start, vma->vm_end, vma->vm_end - vma->vm_start);

		vma = vma->vm_next;
	}
	up_read(&mm->mmap_sem);
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


