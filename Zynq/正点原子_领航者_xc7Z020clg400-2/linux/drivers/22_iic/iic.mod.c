#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x5a808186, "module_layout" },
	{ 0x19c00f3e, "i2c_del_driver" },
	{ 0x506ceef0, "i2c_register_driver" },
	{ 0x80ca5026, "_bin2bcd" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xb6936ffe, "_bcd2bin" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x1a1ca3c4, "device_create" },
	{ 0x78ffc5f8, "__class_create" },
	{ 0x655edb8d, "cdev_add" },
	{ 0xbceb6cbd, "cdev_init" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0x9d669763, "memcpy" },
	{ 0x5f754e5a, "memset" },
	{ 0x18091382, "_dev_err" },
	{ 0x6a1c2ca0, "i2c_transfer" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x203acbbc, "cdev_del" },
	{ 0xb9838f51, "class_destroy" },
	{ 0x1bb38e6b, "device_destroy" },
	{ 0xc5850110, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

MODULE_INFO(depends, "");

