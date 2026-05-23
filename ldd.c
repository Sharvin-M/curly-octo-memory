/* Sharvin's First Linux Device Driver LOL */

/* Header files needed for module macros*/
#include <linux/init.h> 
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YVNG SHRIVS");
MODULE_DESCRIPTION("Sharvin's first basic loadable kernel driver");

/* constructor */
static int sharvin_module_init (void) {
    printk("Sharvin's Driver Says Hi\n");    /* printk prints to the kernel log buffer*/
    return 0;
}

/* destructor */
static void sharvin_module_exit (void) {
    printk("Sharvin's Driver Says Goodbye\n");
}

module_init(sharvin_module_init);
module_exit(sharvin_module_exit);
