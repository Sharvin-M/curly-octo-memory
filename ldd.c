/* Sharvin's First Linux Device Driver LOL. */

/* Header files needed for module macros. */
#include <linux/init.h> 
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YVNG SHRIVS");
MODULE_DESCRIPTION("Sharvin's first basic loadable kernel driver");

static struct proc_dir_entry *sharvin_driver_proc_file; // Declare struct ptr for proc file.
static struct proc_ops sharvin_driver_proc_ops; // Placeholder for proc_ops struct that is passed to proc_create.

/* Constructor. This code is executed when the module is inserted with insmod.
   Here, I am initializing the proc file for my driver. */
static int sharvin_module_init (void) {
    printk("Sharvin's Driver Says Hi\n");    // Print msg to the kernel log buffer, read by 'sudo dmesg'.

    sharvin_driver_proc_file = proc_create("sharvin_driver", // Name for virtual file in proc filesystem.
                                           0, // Some unisgned short that specifies mode, set to 0 for now.
                                           NULL, // Ptr to a parent proc_dir_entry struct, set to NULL for now.
                                           &sharvin_driver_proc_ops); // Ptr to proc_ops struct.
    
    printk("Sharvin's Driver Init is Finished.\n");
    return 0;
}

/* Destructor. This code is executed when the module is removed with rmmod.
   Here, I am destroying the proc file for my driver as a part of the
   cleanup procedure. */
static void sharvin_module_exit (void) {
    printk("Sharvin's Driver Says Goodbye\n");

    proc_remove(sharvin_driver_proc_file);

    printk("Sharvin's Driver Exit is Finished.\n");
}




module_init(sharvin_module_init);
module_exit(sharvin_module_exit);
