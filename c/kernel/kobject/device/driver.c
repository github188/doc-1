#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>

MODULE_AUTHOR("liyunteng");
MODULE_LICENSE("GPL");

extern struct bus_type my_bus_type;

static int my_probe(struct device *dev)
{
	printk("driver found device which my driver can handle.\n");
	return 0;
}

static int my_remove(struct device *dev)
{
	printk("driver found device unpluged.\n");
	return 0;
}

struct device_driver my_driver = {
	.name = "my_dev",
	.bus = &my_bus_type,
	.probe = my_probe,
	.remove = my_remove,
};

static ssize_t mydriver_show(struct device_driver *driver, char *buf)
{
	return sprintf(buf, "%s\n", "This is my driver");
}

static DRIVER_ATTR(drv, S_IRUGO, mydriver_show, NULL);

static int __init my_driver_init(void)
{
	int ret = 0;

	driver_register(&my_driver);
	driver_create_file(&my_driver, &driver_attr_drv);

	return ret;
}

static void __exit my_driver_exit(void)
{
	driver_unregister(&my_driver);
}

module_init(my_driver_init);
module_exit(my_driver_exit);
