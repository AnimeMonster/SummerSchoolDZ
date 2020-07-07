#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/version.h>
#include <linux/types.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniil Belinskiy");
MODULE_DESCRIPTION("Tsundere");
MODULE_VERSION("1.0");

static const char *tsun_phrase = "Where are you looking, Baka?\n";
static const char *DEVICE_NAME = "Tsundere";
static char *msg_ptr = NULL;
static int number_device_open = 0;
static dev_t first;
static struct cdev c_dev;
static struct class *cl;

static int device_open(struct inode *, struct file *);
static int device_realease(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations file_opers = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_realease
};

static int __init tsundere_init(void) {
	int ret;
	struct device *dev_ret;

	if ((ret = alloc_chrdev_region(&first, 0, 1, DEVICE_NAME)) < 0){
		return ret;
	}
	if (IS_ERR(cl = class_create(THIS_MODULE, "chardrv"))){
		unregister_chrdev_region(first, 1);
		return PTR_ERR(cl);
	}
	if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "tsundere"))){
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return PTR_ERR(dev_ret);
	}

	cdev_init(&c_dev, &file_opers);
	if((ret = cdev_add(&c_dev, first, 1)) < 0){
		device_destroy(cl, first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return ret;
	}
	printk(KERN_INFO "Tsundere init\n");
	return 0;
}

static void __exit tsundere_exit(void) {
	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "Tsundere exit\n");
}

static ssize_t device_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
	int bytes_read = 0;

	if (*msg_ptr == 0){
		return 0;
	}

	while (len > 0 && *msg_ptr != 0){
		put_user(*(msg_ptr++), buffer++);
		--len;
		++bytes_read;
	}

	return bytes_read;
}

static ssize_t device_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
	printk(KERN_ALERT "What are you doing, Baka?\n");
	return -EINVAL;
}

static int device_open(struct inode *inode, struct file *filep) {
	msg_ptr = (char *)tsun_phrase;
	number_device_open++;
	printk(KERN_INFO "Device has been opened %d time(s)\n", number_device_open);
	return 0;
}

static int device_realease(struct inode *inode, struct file *filep) {
	--number_device_open;
	printk(KERN_INFO "Device successfully closed\n");
	return 0;
}

module_init(tsundere_init);
module_exit(tsundere_exit);
