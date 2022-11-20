#include<linux/module.h>
#include<linux/platform_device.h>
#include "platform_data.h"

#undef pr_fmt
#define pr_fmt(fmt) "%s : "fmt,__func__

void pdev_release(struct device *dev)
{
	pr_info("Device released \n");
};

//1.create 2 platform data

struct pdev_data pdata[2] = {

	[0] = {.size=512, .perm = RDWR, .sno="SREE246"}, 
	[1] = {.size=1024, .perm = RDWR, .sno="BHANU123"}

};
//2.create 2 platform devices

struct platform_device pf_pdev_1 = {
	.name = "my_pf_dev",
	.id = 0,
	.dev = {
		.platform_data = &pdata[0],
		.release = pdev_release
	}
};

struct platform_device pf_pdev_2 = {
        .name = "my_pf_dev",
	.id = 1,
	.dev = {
		.platform_data = &pdata[1],
		.release = pdev_release
	}
};

static int __init pdev_pltfm_init(void)
{

	//register platform devices
	platform_device_register(&pf_pdev_1);
	platform_device_register(&pf_pdev_2);

	pr_info("Device setup module loaded\n");

	return 0;
}

void __exit pdev_pltfm_exit(void)
{

	//unregister platform devices
        platform_device_unregister(&pf_pdev_1);
        platform_device_unregister(&pf_pdev_2);

	pr_info("Device setup module unloaded\n");

};

module_init(pdev_pltfm_init);
module_exit(pdev_pltfm_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module to register platform devices");
