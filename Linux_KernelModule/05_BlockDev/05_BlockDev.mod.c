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
	{ 0xdd8f8694, "module_layout" },
	{ 0x80e7356f, "put_disk" },
	{ 0x1904ee10, "del_gendisk" },
	{ 0xac2e4be8, "device_add_disk" },
	{ 0xb5a459dc, "unregister_blkdev" },
	{ 0xe60898a9, "blk_cleanup_queue" },
	{ 0xb4ae18ea, "__alloc_disk_node" },
	{ 0xf25c0634, "blk_alloc_queue" },
	{ 0x999e8297, "vfree" },
	{ 0x71a50dbc, "register_blkdev" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xa7eedcc4, "call_usermodehelper" },
	{ 0x56470118, "__warn_printk" },
	{ 0x1e3d005f, "__blk_mq_end_request" },
	{ 0x69acdf38, "memcpy" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x13cc1068, "blk_get_request" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C58396ED5938F0A387BF559");
