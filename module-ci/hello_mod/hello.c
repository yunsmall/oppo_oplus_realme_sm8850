// 最小测试模块：验证与 Ace 6T 设备内核的 vermagic/符号 CRC/CFI 是否兼容
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vermagic.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ace 6T module load test");

static int __init ace6t_test_init(void)
{
	pr_info("ace6t_test: loaded\n");
	pr_info("ace6t_test: vermagic=%s\n", VERMAGIC_STRING);
	return 0;
}

static void __exit ace6t_test_exit(void)
{
	pr_info("ace6t_test: unloaded\n");
}

module_init(ace6t_test_init);
module_exit(ace6t_test_exit);
