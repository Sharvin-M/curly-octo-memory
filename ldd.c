/* Sharvin's First Linux Device Driver LOL. */

/* Header files needed for module macros. */
#include <linux/init.h> 
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YVNG SHRIVS");
MODULE_DESCRIPTION("Sharvin's first basic loadable kernel driver");

static struct proc_dir_entry *sharvin_driver_proc_file; // Declare struct ptr for proc file.


static ssize_t sharvin_driver_write (struct file *file_ptr,
                                     const char *usr_space_buff,
                                     size_t count,
                                     loff_t *offset) {
    
    /* get buffer size */
	size_t procfs_buffer_size = count;
    char * k_mem = kmalloc(count, GFP_KERNEL); 
	

	if ( copy_from_user(k_mem, usr_space_buff, procfs_buffer_size) ) {
		return -EFAULT;
	}

    printk("sharvin_driver_write\n");
	return procfs_buffer_size;

}

static ssize_t sharvin_driver_read (struct file *file_ptr,
                                    char *usr_space_buff,
                                    size_t count,
                                    loff_t *offset) {
    char msg[] = "Blegh!\n";
    size_t len = strlen(msg);
    int return_value;

    if (*offset >= len) {
        return 0;
    }
    
    return_value = copy_to_user(usr_space_buff, msg, len);
    *offset += len;

    printk("sharvin_driver_read\n");
    return len;

}

static struct proc_ops sharvin_driver_proc_ops = {
    .proc_write = sharvin_driver_write,
    .proc_read = sharvin_driver_read
};

/* Constructor. This code is executed when the module is inserted with insmod.
   Here, I am initializing the proc file for my driver. */
static int sharvin_module_init (void) {
    printk("sharvin_module_init: started\n");    // Print msg to the kernel log buffer, read by 'sudo dmesg'.

    sharvin_driver_proc_file = proc_create("sharvin_driver", // Name for virtual file in proc filesystem.
                                           0, // Some unisgned short that specifies mode, set to 0 for now.
                                           NULL, // Ptr to a parent proc_dir_entry struct, set to NULL for now.
                                           &sharvin_driver_proc_ops); // Ptr to proc_ops struct.
    
    printk("sharvin_module_init: finished\n");
    return 0;
}

/* Destructor. This code is executed when the module is removed with rmmod.
   Here, I am destroying the proc file for my driver as a part of the
   cleanup procedure. */
static void sharvin_module_exit (void) {
    printk("sharvin_module_exit: started\n");

    proc_remove(sharvin_driver_proc_file);
    kfree(k_mem);

    printk("sharvin_module_exit: finished\n");
}



module_init(sharvin_module_init);
module_exit(sharvin_module_exit);
