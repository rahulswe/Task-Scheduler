/**
 * MIT License
 * 
 * Copyright (c) 2024 Rahul Singh
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "priority_queue.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/* Function Prototypes */

void initialise_monitor_handles();

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stk_top);

void task1_handler();
void task2_handler();
void task3_handler();
void task4_handler();
void idle_task_handler();

void context_switch();
void select_next_task();
void update_task_state();

/* Global Variables */

TCB_t task_tcb[NUM_TASKS];
priority_queue_t task_rdy_queue;

task_t g_current_task = TASK_1;

uint32_t g_tick_count = 0;

void sw_delay() {
	uint32_t volatile cnt = 0;
	for(cnt = 0; cnt < 100000; cnt++);
}

/* Task Handlers */

/* Note for all the printf:
 * ITM FIFO is a shared resource. So it can get
 * corrupted and may print overwritten messages
 * */

void task1_handler() {
	while(1) {
		sw_delay();
		printf("Task1 Running\n");
	}
}

void task2_handler() {
	while(1) {
		sw_delay();
		printf("Task2 Running\n");
	}
}

void task3_handler() {
	while(1) {
		sw_delay();
#ifdef TEST
		task_tcb[TASK_1].current_state = TASK_BLOCKED;
		task_tcb[TASK_2].current_state = TASK_BLOCKED;
		task_tcb[TASK_4].current_state = TASK_BLOCKED;
		task_tcb[TASK_1].block_cnt = 1000000;
		task_tcb[TASK_2].block_cnt = 1000000;
		task_tcb[TASK_4].block_cnt = 1000000;
#endif
		printf("Task3 Running\n");
	}
}

void task4_handler() {
	while(1) {
		sw_delay();
		printf("Task4 Running\n");
	}
}

void idle_task_handler() {
	while(1) {
		sw_delay();
		printf("Idle Task Running\n");
	}
}

/* Handlers for all the fault exceptions */

void HardFault_Handler(){
	uint32_t *pHFSR = HFSR;
	printf("HardFault Sts Reg Val = %lX\n", *pHFSR);
	printf("Hardfault Handler Called\n");
	while(1);
}

void MemManage_Handler(){
	uint32_t *pCFSR = CFSR;
	printf("MemManageFault Sts Reg Val = %lX\n", (*pCFSR & 0xFF));//or it can be directly accessed using MMFSR 8bit register
	printf("MemManagefault Handler Called\n");
	while(1);
}

void BusFault_Handler(){
	uint32_t *pCFSR = CFSR;
	printf("BusFault Sts Reg Val = %lX\n", (*pCFSR & 0x0000FF00) >> 8);//or it can be directly accessed using BFSR 8bit register
	printf("Busfault Handler Called\n");
	while(1);
}

void UsageFault_Handler(){
	uint32_t *pCFSR = CFSR;
	printf("UsageFault Sts Reg Val = %lX\n", ((*pCFSR) & 0xFFFF0000) >> 16);//or it can be directly accessed using UFSR 16bit register
	printf("Usagefault Handler Called\n");
	while(1);
}

/* Initialization functions */

void init_task_stack(){
	uint32_t *psp;
	for(uint8_t tsk = 0; tsk < NUM_TASKS; tsk++) {
		psp = (uint32_t*)(task_tcb[tsk].psp);
		//stack content -> xpsr, pc, lr, r12, r3, r2, r1, r0, r11 to r4
		//psp is decremented first as in CMx processor, stack utilization method is full descending

		psp--;
		*psp = DUMMY_XPSR;

		psp--;
		*psp = (uint32_t)task_tcb[tsk].task_handler;

		psp--;
		*psp = DUMMY_EXC_RET;

		for(uint8_t i = 0; i < CM4_NUM_GPR; i++) {
			psp--;
			*psp = 0;
		}
		task_tcb[tsk].psp = (uint32_t)psp;
	}

}

void init_tasks() {
	pq_item_t data;

	task_tcb[IDLE_TASK].block_cnt = IDLE_TASK;
	task_tcb[IDLE_TASK].current_state = TASK_READY;
	task_tcb[IDLE_TASK].priority = 1;

	/* enqueue task into the ready queue */
	data.task_id = IDLE_TASK;
	data.priority = task_tcb[IDLE_TASK].priority;
	pq_enqueue(&task_rdy_queue, data);

	for(uint8_t tsk = TASK_1; tsk < NUM_TASKS; tsk++) {
		task_tcb[tsk].block_cnt = 0;
		task_tcb[tsk].current_state = TASK_READY;
		task_tcb[tsk].priority = 1+tsk;

		/* enqueue task into the ready queue */
		data.task_id = tsk;
		data.priority = task_tcb[tsk].priority;
		pq_enqueue(&task_rdy_queue, data);
	}

	task_tcb[IDLE_TASK].psp = IDLE_TASK_STACK_START;
	task_tcb[TASK_1].psp = T1_STACK_START;
	task_tcb[TASK_2].psp = T2_STACK_START;
	task_tcb[TASK_3].psp = T3_STACK_START;
	task_tcb[TASK_4].psp = T4_STACK_START;

	task_tcb[IDLE_TASK].task_handler = idle_task_handler;
	task_tcb[TASK_1].task_handler = task1_handler;
	task_tcb[TASK_2].task_handler = task2_handler;
	task_tcb[TASK_3].task_handler = task3_handler;
	task_tcb[TASK_4].task_handler = task4_handler;


	init_task_stack();
}

void init_systick_timer(uint32_t tick_hz) {

	uint32_t *pSRVR = SYST_RVR;
	uint32_t *pSCSR = SYST_CSR;

	/* set a reload value such that systick exception triggers every 1ms */
	uint32_t reload_val = ((SYSTICK_TIM_CLK/tick_hz) - 1);
	*pSRVR &= ~(0x00FFFFFF);//[23:0] -> reload value
	*pSRVR |= reload_val;//0 to 15999 -> 16000 clock cycles = 1ms

	/* Enable Systick */
	*pSCSR |= 0x07;//clock source -> processor clock, trigger exception when counting down to 0, enable counter
}

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stk_top) {
	/* set MSP to scheduler_stk_top -> This way it is utilizing
	 * a stack area separate from the other task stack */

	//__asm volatile("MSR MSP,%0"::"r"(scheduler_stk_top));
	__asm volatile("MSR MSP,R0");//R0 = function argument
	//return from this function
	__asm volatile("BX LR");
}

void enable_processor_faults(){
	//enable all the configurable fault exceptions
	uint32_t *pSHCSR = SHCSR;
	*pSHCSR |= (1 << BITP_USAGEFAULT_EN);
	*pSHCSR |= (1 << BITP_BUSFAULT_EN);
	*pSHCSR |= (1 << BITP_MEMFAULT_EN);
}

/* Utility functions */

uint32_t get_psp_value(){
	return task_tcb[g_current_task].psp;
}

void save_psp_value(uint32_t psp_val) {
	task_tcb[g_current_task].psp = psp_val;
}

void update_tick_count(){
	g_tick_count++;
	/* TODO: check how to handle overflow */
}

uint32_t get_tick_count(){
	return g_tick_count;
}

void task_delay(uint32_t delay_ms) {
	/*
	 * NOTE: Below global variables are shared resources between exception handlers and thread mode code.
	 * There could be a case of RACE CONDITION between thread mode code and handler mode code.
	 * They may both attempt to access/modify these shared global resource during the same time,
	 * which can lead to undefined result. To avoid this situation, protect it while accessing it
	 * in the thread mode code by disabling the exceptions so that exception handler doesn't get called.
	 * */

	/* Note that for some real time applications, it is not desirable to disable interrupts
	as it can compromise on the real time performance. So we need to be careful with its use. */
	DISABLE_EXCEPTIONS(); //disables all the configurable priority exceptions

	if(g_current_task != IDLE_TASK) {
		task_tcb[g_current_task].block_cnt = g_tick_count + delay_ms;//handle overflow/roll over case
		task_tcb[g_current_task].current_state = TASK_BLOCKED;
		//trigger context switching
		context_switch();
	}

	ENABLE_EXCEPTIONS(); //enable all the configurable priority exceptions
}

__attribute__((naked)) void switch_from_msp_to_psp(){
	/* initialize PSP as it is not automatically done by the processor */
	/* initialize PSP with the PSP value of the first task to run lets say task 1 */
	__asm volatile("PUSH {LR}");//preserve LR as it is needed at the end of this function to return back to main
	__asm volatile("BL get_psp_value");//"branch with link" instead of just "branch" as we want control to reach back here after that function return
	__asm volatile("MSR PSP,R0");//initialize the PSP
	__asm volatile("POP {LR}");


	/* switch MSP to PSP */
	__asm volatile("MRS R0,CONTROL");
	__asm volatile("MOV R0,#0x02");
	__asm volatile("MSR CONTROL,R0");
	__asm volatile("BX LR");
}

/* ROUND ROBIN PRE-EMPTIVE SCHEDULER IMPLEMENTATION */

void context_switch() {
	/* pend the pendSV exception */
	uint32_t *pICSR = ICSR;
	*pICSR |= (1 << BITP_PENDSV_SET);
}

void select_next_task() {
	/* get the task with highest priority
	 * from the task ready queue. At least
	 * idle task is guaranteed to be present
	 * all the time in the queue. */
	pq_item_t top = pq_peek(&task_rdy_queue);
	g_current_task = top.task_id;
}

void update_task_state(){
	/* handle task blocking and unblocking */
	for(uint8_t tsk = TASK_1; tsk < NUM_TASKS; tsk++) {
		if(task_tcb[tsk].current_state == TASK_BLOCKED) {
			if(g_tick_count >= task_tcb[tsk].block_cnt){
				task_tcb[tsk].block_cnt = 0U;
				task_tcb[tsk].current_state = TASK_READY;
			}
		}
	}
}

void SysTick_Handler() {

	/* increment tick count */
	update_tick_count();
	update_task_state();
	context_switch();
}

__attribute__((naked)) void PendSV_Handler(){
	__asm volatile("PUSH {LR}");

	/* SAVE CONTEXT OF THE CURRENT TASK */

	/* processor automatically stores SF1 for the
	 * current task using PSP = current task PSP */

	//get the PSP for the current task
	__asm volatile("MRS R0,PSP");

	//save SF2 for the current task using its PSP
	__asm volatile("STMDB R0!,{R4-R11}");

	/* WOULDN'T THESE REGISTER HAVE GOT UPDATED BY OTHER HIGHER PRIO ISRs BEFORE IT COULD BE SAVED HERE??
	* ANSWER IS NO, BECAUSE AS PER AAPCS THESE REGISTERS R4-R11 VALUE HAVE TO BE PRESERVED BY THE CALLED
	* FUNCTION SO WHICH EVER ISR EXECUTED BEFORE THIS WOULD HAVE PRESERVED THESE REGISTER VALUES BY PUSHING
	* IT ONTO THE STACK VIA MSP AND POPPED IT WHILE EXITING THE ISR */

	//save PSP for the current task
	__asm volatile("BL save_psp_value");

	/* RETRIEVE THE CONTEXT OF THE NEXT TASK */

	//decide which next task should run
	__asm volatile("BL select_next_task");
	//get PSP for the next task
	__asm volatile("BL get_psp_value");
	//restore/pop SF2 for the next task using its PSP
	__asm volatile("LDMIA R0!,{R4-R11}");
	//SET PSP = NEXT TASK PSP
	__asm volatile("MSR PSP,R0");

	/* processor automatically restores SF1 for the next task,
	 * its execution resumes from the location stored in SF1 PC */

	//__asm volatile("POP {LR}");
	//__asm volatile("BX LR");
	__asm volatile("POP {PC}");
}

void start_scheduler(void) {
	init_systick_timer(TICK_HZ);

	/* switch from MSP to PSP initialized to the Task1 PSP Start
	 * Note: Till this point MSP was used which was initialized to the
	 * the top of stack = Task1 PSP Start */
	switch_from_msp_to_psp();

	/* launch one of the task */
	g_current_task = TASK_1;
	task1_handler();
}

/* Main Function */
int main(void)
{
	/* Initialization */

	enable_processor_faults();

	initialise_monitor_handles();

	printf("Application Running\n");

	/* setting MSP to a scheduler stack start which
	 * is pointing to the top of scheduler stack area
	 * to keep a separate stack for handler mode code
	 * that utilizes the stack via MSP */
	init_scheduler_stack(SCHEDULER_STACK_START);

	init_tasks();

	/* start scheduler */
	start_scheduler();

    /* Loop forever */
	for(;;);
}
