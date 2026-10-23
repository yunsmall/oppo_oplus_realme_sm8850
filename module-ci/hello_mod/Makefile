obj-m += hello.o
obj-m += sg_bypass.o

# 内核源码树在本仓库的 common/ 下（CI 下载），本地可覆盖 KDIR
KDIR ?= $(CURDIR)/../../common
OUT ?= $(KDIR)/out

all:
	$(MAKE) -C $(KDIR) O=$(OUT) M=$(CURDIR) modules

clean:
	$(MAKE) -C $(KDIR) O=$(OUT) M=$(CURDIR) clean
