#include "mm.h"
#include "sched.h"
#include "entry.h"
#include "printf.h"

int copy_process(unsigned long fn, unsigned long arg)
{
	preempt_disable();
	struct task_struct *p;

	p = (struct task_struct *) get_free_page();
	if (!p)
		return 1;
	p->priority = current->priority;
	p->state = TASK_RUNNING;
	p->counter = p->priority;
	p->preempt_count = 1; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
	int pid = nr_tasks++;
	task[pid] = p;	
	

	printf("\n\r===== Task: %d =====\n\r", pid);
	printf("* Address: 0x%08x\n\r", p);
	switch (p->state)
	{
	case TASK_RUNNING:
		printf("* State: Running\n\r");
		break;
	default:
		printf("* State: Unkown\n\r");
		break;
	}
	printf("* Priority: %x\n\r", p->priority);
	printf("* Conter: %x\n\r", p->counter);
	printf("* Cpu_Context.x19: 0x%08x\n\r", p->cpu_context.x19);
	printf("* Cpu_Context.x20: 0x%08x\n\r", p->cpu_context.x20);
	printf("* Cpu_Context.pc: 0x%08x\n\r", p->cpu_context.pc);
	printf("* Cpu_Context.sp: 0x%08x\n\r", p->cpu_context.sp);
	printf("===================\n\r\n\r");

	preempt_enable();
	return 0;
}
