#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Debashis Mahanty");
MODULE_DESCRIPTION("our first trail based linux device driver");

char user_space_buffer_[50] = "hello\nhow are you\n";
bool firsttime = true;
int value=0;
struct proc_dir_entry *ldd_proc_create;
static ssize_t	ldd_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t	ldd_write(struct file *, const char __user *, size_t, loff_t *);
struct proc_ops ldd_proc_ops = {
    .proc_read = &ldd_read,
    .proc_write = &ldd_write,
};
static int init_cons_call(void)
{
    printk("Hello welcome to linux device driver\n");
    ldd_proc_create = proc_create("debashis",
                                     0666,
                                     NULL,
                                     &ldd_proc_ops);
    return 0;
}
static void exit_des_call(void)
{
    proc_remove(ldd_proc_create);
    printk("Bye exited the driver successfully\n");
}

static ssize_t	ldd_read(struct file* filepointer, char *user_space_buffer, size_t count, loff_t *offset)
{
    
    size_t len = strlen(user_space_buffer_);

    if(*offset >= len)
    {
        return 0;
    }
    uint8_t result = copy_to_user(user_space_buffer,user_space_buffer_,len);
    printk("File try to read for: %d\n",++value);
    *offset += len;
    return len;
}
static ssize_t	ldd_write(struct file* filepointer, const char *user_space_buffer, size_t count, loff_t *offset)
{
    if (count > sizeof(user_space_buffer_) - 1 )
        count = sizeof(user_space_buffer_) - 1;  // Prevent overflow

    if(strlen(user_space_buffer_) == sizeof(user_space_buffer_)-1)
    {
        printk("overflow protected trigger\n");
        return count;
    }

    if (copy_from_user(user_space_buffer_, user_space_buffer, count) != 0)
        return -EFAULT;

    user_space_buffer_[count] = '\0';  // Null-terminate if it's a string
    printk("data is: %s\n", user_space_buffer_);
    
    return count;
}

module_init(init_cons_call);
module_exit(exit_des_call);