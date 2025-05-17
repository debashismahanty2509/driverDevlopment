#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>


MODULE_AUTHOR("Debashis Mahanty");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This project is to pass the parameter in argument");
int vIntadd,fixedarr[4];
char *vchar;
module_param(vIntadd,int,S_IRUSR|S_IWUSR);
module_param(vchar,charp,S_IRUSR|S_IWUSR);
module_param_array(fixedarr,int,NULL,S_IRUSR|S_IWUSR);
int myOwnsetvalue(const char *val, const struct kernel_param *kp)
{
    printk(KERN_INFO "Callback called to change the value vIntadd %s\n",kp->name);
    int res = param_set_int(val, kp); // Use helper for write variable
    if(res == 0)
    {
        printk(KERN_INFO "New value of vIntadd = %d\n", vIntadd);
        return 0;
    }
    return -1;
}
void freeownpointer(void *arg)
{
    if(vchar != NULL)
    {
        free(vchar);
    }
}
struct kernel_param_ops myparopt{
	/* How the ops should behave */
    .flags=0;
	/* Returns 0, or -errno.  arg is in kp->arg. */
	.set = &myOwnsetvalue;
	/* Returns length written or -errno.  Buffer is 4k (ie. be short!) */
	.get = &myOwnsetvalue;//(char *buffer, const struct kernel_param *kp);
	/* Optional function to free kp->arg when module unloaded. */
	.free = &freeownpointer;
};

module_param_cb(vIntadd, &myparopt, &vIntadd, S_IRUGO|S_IWUSR );

static int init_cons_call()
{
    int i;
        printk(KERN_INFO "ValueETX = %d  \n", vIntadd);
        printk(KERN_INFO "NameETX = %s \n", vchar);
        for (i = 0; i < (sizeof arr_valueETX / sizeof (int)); i++) {
                printk(KERN_INFO "Arr_value[%d] = %d\n", i, fixedarr[i]);
        }
        printk(KERN_NOTICE "Kernel Module Inserted Successfully...\n");
    return 0;
}
static void exit_des_call()
{
    freeownpointer(NULL);
    printk(KERN_NOTICE "ldd_arg_pass project stopped executing\n");
}

module_init(init_cons_call);
module_exit(exit_des_call);