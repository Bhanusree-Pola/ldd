#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/uaccess.h>
#include <linux/platform_device.h>
#include "platform_data.h"


#undef pr_fmt
#define pr_fmt(fmt) "%s : " fmt,__func__

loff_t pd_lseek(struct file *filp, loff_t offset, int whence)
{
	return 0;
}

ssize_t pd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	return 0;
}

ssize_t pd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	return 0;
}


int check_permission(int dev_perm, int acc_mode)
{

	if(dev_perm == RDWR)
		return 0;
	
	//ensures readonly access
	if( (dev_perm == RDONLY) && ( (acc_mode & FMODE_READ) && !(acc_mode & FMODE_WRITE) ) )
		return 0;
	
	//ensures writeonly access
	if( (dev_perm == WRONLY) && ( (acc_mode & FMODE_WRITE) && !(acc_mode & FMODE_READ) ) )
		return 0;

	return -EPERM;

}


int pd_open(struct inode *inode, struct file *filp)
{

	return 0;
}

int pd_release(struct inode *inode, struct file *flip)
{
	pr_info("release was successful\n");

	return 0;
}


/* file operations of the driver */
struct file_operations pd_fops=
{
	.open = pd_open,
	.release = pd_release,
	.read = pd_read,
	.write = pd_write,
	.llseek = pd_lseek,
	.owner = THIS_MODULE
};

int pd_dr_remove(struct platform_device *pdev)
{
	pr_info("A device is removed\n");
	return 0;
}

int pd_dr_probe(struct platform_device *pdev)
{
	pr_info("A device is detected\n");
	return 0;
}

struct platform_driver pd_platform_driver = {

	.probe = pd_dr_probe,
	.remove = pd_dr_remove,
	.driver = {
		.name = "my_pf_dev"
	}
};

static int __init pd_driver_init(void)
{
	platform_driver_register(&pd_platform_driver);
	pr_info("Driver Module loaded\n");
	return 0;
}

static void __exit pd_driver_cleanup(void)
{
	platform_driver_unregister(&pd_platform_driver);
	pr_info("Driver Module Unloaded\n");
}

module_init(pd_driver_init);
module_exit(pd_driver_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bhanusree Pola");
MODULE_DESCRIPTION("Skeleton Platform driver");
