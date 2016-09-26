#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/miscdevice.h>
#include<asm/uaccess.h>
#include<linux/sched.h>

#define MISC_DEV_NAME "wait_demo"
#define BUF_SIZE (256)
static char g_buffer[BUF_SIZE];

static int buffer_count = 0;

static wait_queue_head_t  wait_queue;

ssize_t misc_read(struct file * fp, char __user * buf, size_t r_size, loff_t * ppos)
{
	ssize_t result = 0;
	if(buffer_count > 0)
	{
		printk("Transfer data from kernel to userspace, size:%d\n", buffer_count);
		if(copy_to_user(buf, g_buffer, buffer_count))
		{
			printk("Transfer data fail.\n");
			return -EINVAL;
		}
		result = buffer_count;
		buffer_count = 0;
		/*wakeup the process which wait the wait_queue*/
		wake_up_interruptible(&wait_queue);
	}
	else
	{
		printk("There is no data to transfer.\n");
		return 0;
	}
	return result;
}

ssize_t misc_write (struct file *fp , const char __user * buf, size_t w_size, loff_t * ppos)
{
	ssize_t result = 0;
	memset(g_buffer, 0, BUF_SIZE);
	/*suspend current process utill buffer_count is zero*/
	wait_event_interruptible(wait_queue, buffer_count == 0);

	if(copy_from_user(g_buffer, buf, w_size))
	{
		printk("Recv data from user space fail.\n");
		return -EINVAL;
	}
	result = w_size;
	buffer_count = w_size;
	printk("Recv data from user space successfully, size:%d\n", buffer_count);
	return result;
}


static struct file_operations dev_fops =
{
	.owner = THIS_MODULE,
	.read = misc_read,
	.write = misc_write,
};

static struct miscdevice  misc_wait_dev =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = MISC_DEV_NAME,
	.fops = &dev_fops,
};


static int wait_demo_init(void)
{
	int ret;

	printk(KERN_INFO"Star to load driver.\n");
	memset(g_buffer, 0, BUF_SIZE);
	
	ret = misc_register(&misc_wait_dev);
	if(ret)
	{
		printk("Register the misc dev fail.\n");
		return -1;
	}	
	printk("Register the misc dev successfully.\n");
	
	init_waitqueue_head(&wait_queue);
	return 0;
}

static void wait_demo_exit(void)
{
	printk(KERN_INFO"Unload the driver.\n");
	misc_deregister(&misc_wait_dev);
	printk("deregister the misc wait dev successfully.\n");
	return;
}

module_init(wait_demo_init);
module_exit(wait_demo_exit);
