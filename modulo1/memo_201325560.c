#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/quicklist.h>
#include <linux/swap.h>
#include <linux/swapfile.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>

#define FileProc "memo"
struct sysinfo i;



static int show_memory_stat(struct seq_file *f, void *v){
    si_meminfo(&i);     
    seq_printf(f,"%8lu\n", (i.totalram));
    seq_printf(f,"%8lu\n", (i.freeram));
    seq_printf(f,"%8lu\n", i.freeram / i.totalram);
    seq_printf(f,"%8s\n", "Daniel Alvarez");
    seq_printf(f,"%8s\n", "201325560");
    return 0;
}

static int meminfo_proc_open(struct inode *inode, struct file *file){
    return single_open(file, show_memory_stat, NULL);
}

static const struct file_operations Meminfo_fops = {
    .owner = THIS_MODULE,
    .open = meminfo_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};


static int __init start_function(void)
{
    proc_create(FileProc, 0, NULL, &Meminfo_fops);
    printk(KERN_INFO "201325560 .\n");
    return 0;
}

static void __exit clean_function(void)
{
    remove_proc_entry(FileProc, NULL); 
    printk(KERN_INFO "Sistemas Operativos 1 .\n");
}
 
module_init(start_function);
module_exit(clean_function);
 
MODULE_AUTHOR("Daniel Alvarez");
MODULE_DESCRIPTION("Proyecto 1");
MODULE_LICENSE("GPL");
