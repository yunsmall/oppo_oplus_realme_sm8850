// 拦截 oplus_secure_guard_new 的 execve 上报：
// 只跳过 termux / ksud 的路径，其他安全检测保持原样。
#include <linux/kprobes.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Bypass oplus secureguard root exec report for termux/ksud");

static struct kprobe kp;
static char path_buf[256];

static bool is_own_path(const char *path)
{
	if (!path)
		return false;

	if (copy_from_kernel_nofault(path_buf, path, sizeof(path_buf) - 1))
		return false;
	path_buf[sizeof(path_buf) - 1] = '\0';

	return strstr(path_buf, "/data/data/com.termux") ||
	       strstr(path_buf, "/data/adb/ksu");
}

static int pre_handler(struct kprobe *p, struct pt_regs *regs)
{
	if (is_own_path((const char *)regs->regs[0])) {
		regs->regs[0] = 0;
		regs->pc = regs->regs[30];
		return 1;
	}
	return 0;
}

static int __init sg_bypass_init(void)
{
	kp.symbol_name = "oplus_report_execveat_new";
	kp.pre_handler = pre_handler;
	return register_kprobe(&kp);
}

static void __exit sg_bypass_exit(void)
{
	unregister_kprobe(&kp);
}

module_init(sg_bypass_init);
module_exit(sg_bypass_exit);
