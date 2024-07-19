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

#ifndef MAIN_H
#define MAIN_H

/* 13 general purpose registers (R0-R12) in CM4 processor */
#define CM4_NUM_GPR    (13U)

/* Systick Control and Status Register */
#define SYST_CSR ((uint32_t *const)0xE000E010)
/* Systick Reload Value Register */
#define SYST_RVR ((uint32_t *const)0xE000E014)
/* Systick Current Value Register */
#define SYST_CVR ((uint32_t *const)0xE000E018)

/* Fault related registers */
#define SHCSR (uint32_t *const)0xE000ED24
#define CFSR (uint32_t *const)0xE000ED28
#define HFSR (uint32_t *const)0xE000ED2C
#define ICSR (uint32_t *const)0xE000ED04

#define BITP_USAGEFAULT_EN    (18U)
#define BITP_BUSFAULT_EN      (17U)
#define BITP_MEMFAULT_EN      (16U)
#define BITP_PENDSV_SET       (28U)

#define HSI_CLOCK (16000000U)
#define SYSTICK_TIM_CLK (HSI_CLOCK) //16MHz -> 16000000 clock cycles per second
#define TICK_HZ    (1000U) //1000 Systick Exceptions per second

#define SRAM_START (0x20000000U)
#define SRAM_SIZE  ((128U) * (1024U))
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE)) //0x20020000

#define T1_STACK_START  (SRAM_END) //0x20020000
#define T2_STACK_START  (T1_STACK_START - (1024U)) //0x2001FC00
#define T3_STACK_START  (T2_STACK_START - (1024U)) //0x2001F800
#define T4_STACK_START  (T3_STACK_START - (1024U)) //0x2001F400

#define SCHEDULER_STACK_START  ((T4_STACK_START) - (1024U)) //0x2001F000
#define IDLE_TASK_STACK_START  ((SCHEDULER_STACK_START) - 512U)

#define DUMMY_XPSR     (0x01000000U)
#define DUMMY_EXC_RET  (0xFFFFFFFDU)

#define DISABLE_EXCEPTIONS() do{__asm volatile("MOV R0,#0x01"); __asm volatile("MSR PRIMASK,R0");} while(0)
#define ENABLE_EXCEPTIONS()  do{__asm volatile("MOV R0,#0x00"); __asm volatile("MSR PRIMASK,R0");} while(0)

typedef enum {
	TASK_READY = 0,
	TASK_BLOCKED
} task_state_t;

typedef enum {
	IDLE_TASK = 0,
	TASK_1,
	TASK_2,
	TASK_3,
	TASK_4,
	NUM_TASKS
} task_t;

typedef struct {
	uint8_t priority;
	uint32_t psp;
	uint32_t block_cnt;//blocking duration
	task_state_t current_state;
	void (*task_handler)();
} TCB_t;
#endif
