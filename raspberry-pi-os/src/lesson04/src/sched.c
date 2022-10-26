#include "sched.h"
#include "irq.h"
#include "printf.h"

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct * task[NR_TASKS] = {&(init_task), };
int nr_tasks = 1;

void preempt_disable(void)
{
	current->preempt_count++;
}

void preempt_enable(void)
{
	current->preempt_count--;
}


void _schedule(void)
{
	preempt_disable();
	int next,c;
	struct task_struct * p;
	while (1) {
		c = -1;
		next = 0;
		for (int i = 0; i < NR_TASKS; i++){
			p = task[i];
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				c = p->counter;
				next = i;
			}
		}
		if (c) {
			break;
		}
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
	if(task[next] != current){
		printf("schedule switched to %d\r\n", next);
		printf("\n\r===== Task: %d =====\n\r", next);
		printf("* Address: 0x%08x\n\r", task[next]);
		switch (task[next]->state)
		{
			case TASK_RUNNING:
				printf("* State: Running\n\r");
				break;
			default:
				printf("* State: Unknown\n\r");
				break;
		}
		printf("* Priority: %x\n\r", task[next]->priority);
		printf("* Conter: %x\n\r", task[next]->counter);
		printf("* Cpu_Context.x19: 0x%08x\n\r", task[next]->cpu_context.x19);
		printf("* Cpu_Context.x20: 0x%08x\n\r", task[next]->cpu_context.x20);
		printf("* Cpu_Context.pc: 0x%08x\n\r", task[next]->cpu_context.pc);
		printf("* Cpu_Context.sp: 0x%08x\n\r", task[next]->cpu_context.sp);
		printf("===================\n\r\n\r");
	}
	switch_to(task[next]);
	preempt_enable();
}

void schedule(void)
{
	current->counter = 0;
	_schedule();
}

void switch_to(struct task_struct * next) 
{
	if (current == next) 
		return;
	struct task_struct * prev = current;
	current = next;
	cpu_switch_to(prev, next);
}

void schedule_tail(void) {
	preempt_enable();
}


void timer_tick()
{
	--current->counter;
	if (current->counter>0 || current->preempt_count >0) {
		return;
	}
	current->counter=0;
	enable_irq();
	_schedule();
	disable_irq();
}
