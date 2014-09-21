#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include "asm/io.h"
#include "asm/uaccess.h"

#define DEVICE_NAME	"GPIODEVICE"
#define GPIO_MAJOR 231
#define GPIO_MAGIC 0xBB

#define CMD_SOME	_IO(GPIO_MAGIC, 0)

/* 设置主设备号 */
static int gpio_major = GPIO_MAJOR;

struct gpio_dev {
	struct cdev cdev;
	struct semaphore sem;
};

struct gpio_dev *gpio_devp;

/* gpio open */
static int gpio_open(struct inode *inode, struct file *filp)
{
	struct gpio_dev *dev;
	dev = container_of(inode->i_cdev, struct gpio_dev, cdev);
	filp->private_data = dev;
	printk("gpio device opened.\n");
	return 0;
}

/* gpio release */
int gpio_release(struct inode *inode, struct file *filp)
{
	printk("gpio device released.\n");
	return 0;
}

static ssize_t gpio_read(struct file *filp, char __user *buf, size_t count,
	loff_t offp)
{
	struct gpio_dev *dev = filp->private_data;
	down(&dev->sem);
	printk("gpio device readed.\n");
	up(&dev->sem);
	return 0;
}

static ssize_t gpio_write(struct file *filp, const char __user *buf,
			  size_t size, loff_t *ppos)
{
	struct gpio_dev *dev = filp->private_data;
	down(&dev->sem);
	printk("gpio device write.\n");
	up(&dev->sem);
	return 0;
}

static int gipi_ioctl(struct inode *inode, struct file *file,
		      unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
	case CMD_SOME:
		return 0;
	default:
		return -EINVAL;
	}
		
}

/* file operations */
static struct file_operations gpio_fops = {
	.owner = THIS_MODULE,
	.open = gpio_open,
	.release = gpio_release,
	.write = gpio_write,
	.ioctl = gpio_ioctl,
};

/* init cdev */
static void gpio_setup_cdev(struct gpio_dev *dev, int index)
{
	int err;
	int devno = MKDEV(gpio_major, index);

	/* 初始化cdev 建立与fops的连接 */
	cdev_init(&dev->cdev, &gpio_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &gpio_fops;

	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk("add gpio device failed: %d.\n", err);
}

static int gpio_init(void)
{
	int result;
	dev_t devno = MKDEV(gpio_major, 0);

	if (gpio_major) {
		result = register_chrdev_region(devno, 1, DEVICE_NAME);
	} else {
		result = alloc_chrdev_region(&devno, 0, 1, DEVICE_NAME);
		gpio_major = MAJOR(devno);
	}

	if (result < 0) {
		printk("register failed.\n");
		return result;
	}


	gpio_devp = kmalloc(sizeof(struct gpio_dev), GFP_KERNEL);

	if (!gpio_devp) {
		result = -ENOMEM;
		unregister_chrdev_region(devno, 1);
		return result;
	}

	memset(gpio_devp, 0, sizeof(struct gpio_dev));
	gpio_setup_cdev(gpio_devp, 0);

	INIT_MUTEX(&gpio_dev->sem);
	init_MUTEX(&gpio_devp->sem);
	printk("gpio init done.\n");
	return 0;
}

static void gpio_exit(void)
{
	cdev_del(&gpio_devp->cdev);
	kfree(gpio_devp);
	unregister_chrdev_region(MKDEV(gpio_major, 0), 1);
	printk("gpio device exit.\n");
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_AUTHOR("liyunteng");
MODULE_DESCRIPTION("GPIO Driver");
MODULE_LICENSE("GPL");
