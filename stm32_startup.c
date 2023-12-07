#include <stdint.h>

#define SRAM_START (0x20000000U)
#define SRAM_SIZE  (128 * 1024) //128KB
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END // we are placing stack at the end of the RAM

extern uint32_t __etext;
extern uint32_t __sdata;
extern uint32_t __edata;
extern uint32_t __ebss;
extern uint32_t __sbss;
extern uint32_t __la_data;

/* prototype of main() function */
int main();

void __libc_init_array();
 
void Reset_Handler(void);

void NMI_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));

uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
	STACK_START,
	(uint32_t)&Reset_Handler,
	(uint32_t)&NMI_Handler,
	(uint32_t)&HardFault_Handler,
	(uint32_t)&MemManage_Handler,
	(uint32_t)&BusFault_Handler,
	(uint32_t)&UsageFault_Handler,
	0, 
	0, 
	0, 
	0,
	(uint32_t)&SVC_Handler,
	(uint32_t)&DebugMon_Handler,
	0,
	(uint32_t)&PendSV_Handler,
	(uint32_t)&SysTick_Handler,
};

void Reset_Handler() {
	// system clock initialization


	//copy .data section from flash to SRAM
	uint32_t size = (uint32_t)&__edata - (uint32_t)&__sdata;

	uint8_t *pSrc = (uint8_t*)&__etext;//instead of __etext as there are other sections between .text and .data now
	uint8_t *pDst = (uint8_t*)&__sdata;

	for(uint32_t i = 0; i < size; i++) {
		*pDst++ = *pSrc++;
	}

	//initialize .bss section
	pDst = (uint8_t*)&__sbss;
	size = &__ebss - &__sbss;

	for(uint32_t i = 0; i < size; i++) {
		*pDst++ = 0;
	}
	//initiliate std c library
	__libc_init_array();

	//call main()
	main();
}

void Default_Handler() {

}