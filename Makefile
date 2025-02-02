# Module name (without .c extension)
MODULE_NAME := taskList

# Kernel build directory
KERNEL_DIR := /lib/modules/$(shell uname -r)/build

# Compiler flags
obj-m := $(MODULE_NAME).o

# Default target: Build the module
all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

# Clean target: Remove generated files
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

# Load the module
load:
	sudo insmod $(MODULE_NAME).ko

# Unload the module
unload:
	sudo rmmod $(MODULE_NAME)

# Show module info
info:
	modinfo $(MODULE_NAME).ko
