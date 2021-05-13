#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage long sys_hello(void) {
printk("Hello, World!\n");
return 0;
}

asmlinkage long sys_set_weight (int weight)
{
    if (weight<0)
    {
        return -EINVAL;
    }
    current->task_weight=weight;
    return 0;
}

asmlinkage long sys_get_weight(void)
{
    return current->task_weight;
}

long sum_children(struct task_struct* curr_node){
    struct list_head* list;
	long total = curr_node->task_weight;
	struct task_struct* child;
	if(list_empty(&(curr_node->children))){
		return total;
	}
	list_for_each(list, &(curr_node->children)){
		child =list_entry(list,struct task_struct, sibling);
		total+=sum_children(child);
	}
	return total;
}

asmlinkage long sys_get_children_sum(void)
{
    if (list_empty(&(current->children)))
    {
		return -ECHILD;
	} 
    else
    {
        return sum_children(current)-current->task_weight ;
    }
	
}


asmlinkage long sys_get_heaviest_ancestor(void)
{
    long max_weight = 0;
    struct task_struct *temp;
    temp = current;
    pid_t max_pid;
    while(temp->pid != 0)
    {
        if (temp->task_weight >= max_weight)
        {
            max_weight = temp->task_weight;
            max_pid = temp->pid;
        }
        temp = temp->real_parent;
    }
        if (temp->task_weight > max_weight)
        {
            max_weight = temp->task_weight;
            max_pid = temp->pid;
        }
    return max_pid;
}