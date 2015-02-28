
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
//#include <asm/system.h>
#include <asm/uaccess.h>

#define MOUSEY_BASE   0×300

int MOUSEY_MAJOR = 60;

int MOUSEY_MINOR = ?????;

MODULE_LICENSE("GPL");

//char *memory_buffer;

int mousey_open(struct inode *inode, struct file *filp);
int mousey_release(struct inode *inode, struct file *filp);
ssize_t mousey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t mousey_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void mousey_exit(void);
int mousey_init(void);

struct file_operations mousey_fops = {
	read:   mousey_read,
	write:  mousey_write,
	open:   mousey_open,
	release:mousey_release,
	poll:   mousey_poll
};



static struct miscdevice mousey = {
	MOUSEY_MINOR, 
	“ourmouse”,
	&mousey_fops
};

module_init(mousey_init);
module_exit(mousey_exit);

int mousey_init(void){
	/*
	if(check_region(MOUSEY_BASE, 3))
		return -ENODEV;
	request_region(MOUSEY_BASE, 3, “mousey”);

	misc_register(&our_mouse);
	return 0;


	int result;
	result = register_chrdev(memory_major, "memory", &memory_fops);
	if (result < 0){
		printk("<1>memory: cannot obtain major number %d\n", memory_major);
		return result;
	}

	memory_buffer = kmalloc(1, GFP_KERNEL);
	if (!memory_buffer) {
		result = -ENOMEM;
		goto fail;
	}
	memset(memory_buffer, 0, 1);

	printk("<1>Inserting memory module\n");
	return 0;

	fail:
	memory_exit();
	return result;
	*/
	return 0;
}

void mousey_exit(void){
/*
    misc_deregister(&our_mouse);

    free_region(OURMOUSE_BASE, 3);


	unregister_chrdev(memory_major, "memory");

	if(memory_buffer)
		kfree(memory_buffer);

	printk("<1>Removing memory module\n");
*/
}

int mousey_open(struct inode *inode, struct file *filp){
/*
    if(mouse_users++)
        return 0;
    if(request_irq(mouse_intr, OURMOUSE_IRQ, 0,
       “ourmouse”, NULL))
    {
        mouse_users–;
        return -EBUSY;
    }
    mouse_dx = 0;
    mouse_dy = 0;
    mouse_buttons = 0;
    mouse_event = 0;
    MOD_INC_USE_COUNT;
*/
	return 0;
}

int mousey_release(struct inode *inode, struct file *filp){
/*
    if(–mouse_users)

            return 0;

    free_irq(OURMOUSE_IRQ, NULL);

    MOD_DEC_USE_COUNT;

    return 0;
*/
	return 0;
}


ssize_t mousey_read(struct file *filp, char *buffer, size_t count, loff_t *f_pos){
/*
	copy_to_user(buf, memory_buffer, 1);

	if (*f_pos == 0){
		*f_pos+=1;
		return 1;
	} else {
		return 0;
	}
*/
	if(put_user(0, buffer))
		return -EFAULT;
	if(put_user(0, buffer+1))
		return -EFAULT;
	if(put_user(-10, buffer+2))
		return -EFAULT;
}

ssize_t mousey_write(struct file *filp, char *buf, size_t count, loff_t *f_pos){
/*
 return -EINVAL;
*/
/*
	char *tmp;
	tmp =buf+count-1;
	copy_from_user(memory_buffer, tmp, 1);
	return 1;
*/
	return -EINVAL;
}

static unsigned int mousey_poll(struct file *file, poll_table *wait){
/*	
	poll_wait(file, &mouse_wait, wait);
	if(mouse_event)
		return POLLIN | POLLRDNORM;
	return 0;
*/
	return POLLIN | POLLRDNORM;
}




/*
static struct wait_queue *mouse_wait;

static spinlock_t mouse_lock = SPIN_LOCK_UNLOCKED;


static void ourmouse_interrupt(int irq, void *dev_id,
struct pt_regs *regs)
{
	char delta_x;
	char delta_y;
	unsigned char new_buttons;

	delta_x = inb(OURMOUSE_BASE);
	delta_y = inb(OURMOUSE_BASE+1);
	new_buttons = inb(OURMOUSE_BASE+2);

	if(delta_x || delta_y || new_buttons != mouse_buttons)
	{
		spin_lock(&mouse_lock);
		mouse_event = 1;
		mouse_dx += delta_x;
		mouse_dy += delta_y;
		mouse_buttons = new_buttons;
		spin_unlock(&mouse_lock);

		wake_up_interruptible(&mouse_wait);
	}
}
*/
