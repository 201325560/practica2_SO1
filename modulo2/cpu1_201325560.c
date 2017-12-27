#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/spinlock.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>

/*para el archivo proc*/
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
/*fin para el archivo proc*/


#include <asm/processor.h>
#include <asm/mmu_context.h>

#define FileProc "cpu_201325560"
struct task_struct *task;


static int mostrar_procesos (struct seq_file *f, void *v)
{
	 for_each_process(task){
	    seq_printf(f,"pid: %d | name: %s | state: %ld\n", task->pid, task->comm, task->state);
  	}
	return 0;
}


static int procesos_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, mostrar_procesos, NULL);
}

static const struct file_operations Procinfo_fops = {
    .owner = THIS_MODULE,
    .open = procesos_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};





static int __init tasks_lister_linear_init(void)
{
  printk(KERN_INFO "Daniel Alvarez\n");	
  proc_create(FileProc, 0, NULL, &Procinfo_fops);
  printk(KERN_INFO "Daniel Alvarez\n");	
  return 0;
}

static void __exit tasks_lister_linear_exit(void)
{
  printk(KERN_INFO "Sistemas Operativos 1\n");
}

module_init(tasks_lister_linear_init);
module_exit(tasks_lister_linear_exit);
 
MODULE_AUTHOR("David Daniel Alvarez Hernandez");
MODULE_DESCRIPTION("modulo2");
MODULE_LICENSE("GPL");
