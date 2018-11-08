#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static struct kmem_cache *my_cache;
static int size = 4*PAGE_SIZE;
static char *buf;

static int __init my_init(void)
{
	my_cache = kmem_cache_create("My test cache", size, 0, SLAB_HWCACHE_ALIGN, NULL);	
	if (!my_cache)
	{
		pr_info("Failed creating cache\n");
		return -1;
	}
	pr_info("Cache allocated\n");

	buf = kmem_cache_alloc(my_cache, GFP_ATOMIC);
	if (!buf)
	{
		pr_info("Failed allocating buffer from cache\n");
		kmem_cache_destroy(my_cache);
		return -1;
	}
	pr_info("Buffer allocated from cache\n");
	return 0;
}

static void __exit my_exit(void)
{
	kmem_cache_free(my_cache, buf);
	pr_info("Buffer freed\n");

	kmem_cache_destroy(my_cache);
	pr_info("Cache freed\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jonas");
MODULE_LICENSE("GPL v2");


