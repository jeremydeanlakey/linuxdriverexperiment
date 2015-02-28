
#include <linux/init.h>
//#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/poll.h>
//#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/miscdevice.h>

#define MOUSEY_BASE   0×300

#define MOUSEY_MINOR 240

MODULE_LICENSE("GPL");  //  a lie to suppress warnings, will change later

int mousey_open(struct inode *inode, struct file *filp);
int mousey_release(struct inode *inode, struct file *filp);
ssize_t mousey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t mousey_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void mousey_exit(void);
int mousey_init(void);
static unsigned int mousey_poll(struct file *file, poll_table *wait);

struct file_operations mousey_fops = {
	read:   mousey_read,
	write:  mousey_write,
	open:   mousey_open,
	release:mousey_release,
	poll:   mousey_poll
};

static struct miscdevice mousey = {
	minor:MOUSEY_MINOR, 
	name:"mousey",
	fops:&mousey_fops
};

module_init(mousey_init);
module_exit(mousey_exit);

int mousey_init(void){
	int result;
	printk (KERN_ALERT "mousey_init called2\n");
	result = misc_register(&mousey);
	printk (KERN_ALERT "mousey_init register result: %d\n", result);
	return 0;
}

void mousey_exit(void){
	misc_deregister(&mousey);
	printk (KERN_ALERT "mousey_exit called\n");
}

int mousey_open(struct inode *inode, struct file *filp){
	printk (KERN_ALERT "mousey_open called\n");
	return 0;
}

int mousey_release(struct inode *inode, struct file *filp){
	printk (KERN_ALERT "mousey_release called\n");
	return 0;
}


ssize_t mousey_read(struct file *filp, char *buffer, size_t count, loff_t *f_pos){
	printk (KERN_ALERT "mousey_read called\n");
	if(count<3)
		return -EINVAL;
	if(put_user(0x80, buffer))
		return -EFAULT;
	if(put_user(0, buffer+1))
		return -EFAULT;
	if(put_user(10, buffer+2))
		return -EFAULT;
	return count;
}

ssize_t mousey_write(struct file *filp, char *buf, size_t count, loff_t *f_pos){
	printk (KERN_ALERT "mousey_write called\n");
	return -EINVAL;
}

static unsigned int mousey_poll(struct file *file, poll_table *wait){
	printk (KERN_ALERT "mousey_poll called\n");
	return POLLIN | POLLRDNORM;
}

