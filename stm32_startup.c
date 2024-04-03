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

void NMI_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy0_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy1_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy2_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy3_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy4_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy5_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy6_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy7_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy8_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy9_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy10_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy11_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy12_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy13_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy14_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy15_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy16_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy17_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy18_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy19_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy20_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy21_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy22_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy23_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy24_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy25_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy26_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy27_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy28_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy29_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy30_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy31_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy32_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy33_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy34_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy35_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy36_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy37_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy38_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy39_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy40_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy41_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy42_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy43_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy44_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy45_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy46_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy47_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy48_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy49_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy50_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy51_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy52_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy53_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy54_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy55_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy56_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy57_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy58_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy59_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy60_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy61_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy62_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy63_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy64_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy65_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy66_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy67_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy68_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy69_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy70_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy71_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy72_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy73_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy74_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy75_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy76_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy77_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy78_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy79_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy80_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy81_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy82_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy83_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy84_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy85_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy86_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy87_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy88_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy89_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy90_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy91_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy92_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy93_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy94_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy95_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void dummy96_handler  				(void) __attribute__ ((weak, alias("Default_Handler")));

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
	#if 1
	(uint32_t)&dummy0_handler,
	(uint32_t)&dummy1_handler,
	(uint32_t)&dummy2_handler,
	(uint32_t)&dummy3_handler,
	(uint32_t)&dummy4_handler,
	(uint32_t)&dummy5_handler,
	(uint32_t)&dummy6_handler,
	(uint32_t)&dummy7_handler,
	(uint32_t)&dummy8_handler,
	(uint32_t)&dummy9_handler,
	(uint32_t)&dummy10_handler,
	(uint32_t)&dummy11_handler,
	(uint32_t)&dummy12_handler,
	(uint32_t)&dummy13_handler,
	(uint32_t)&dummy14_handler,
	(uint32_t)&dummy15_handler,
	(uint32_t)&dummy16_handler,
	(uint32_t)&dummy17_handler,
	(uint32_t)&dummy18_handler,
	(uint32_t)&dummy19_handler,
	(uint32_t)&dummy20_handler,
	(uint32_t)&dummy21_handler,
	(uint32_t)&dummy22_handler,
	(uint32_t)&dummy23_handler,
	(uint32_t)&dummy24_handler,
	(uint32_t)&dummy25_handler,
	(uint32_t)&dummy26_handler,
	(uint32_t)&dummy27_handler,
	(uint32_t)&dummy28_handler,
	(uint32_t)&dummy29_handler,
	(uint32_t)&dummy30_handler,
	(uint32_t)&dummy31_handler,
	(uint32_t)&dummy32_handler,
	(uint32_t)&dummy33_handler,
	(uint32_t)&dummy34_handler,
	(uint32_t)&dummy35_handler,
	(uint32_t)&dummy36_handler,
	(uint32_t)&dummy37_handler,
	(uint32_t)&dummy38_handler,
	(uint32_t)&dummy39_handler,
	(uint32_t)&dummy40_handler,
	(uint32_t)&dummy41_handler,
	(uint32_t)&dummy42_handler,
	(uint32_t)&dummy43_handler,
	(uint32_t)&dummy44_handler,
	(uint32_t)&dummy45_handler,
	(uint32_t)&dummy46_handler,
	(uint32_t)&dummy47_handler,
	(uint32_t)&dummy48_handler,
	(uint32_t)&dummy49_handler,
	(uint32_t)&dummy50_handler,
	(uint32_t)&dummy51_handler,
	(uint32_t)&dummy52_handler,
	(uint32_t)&dummy53_handler,
	(uint32_t)&dummy54_handler,
	(uint32_t)&dummy55_handler,
	(uint32_t)&dummy56_handler,
	(uint32_t)&dummy57_handler,
	(uint32_t)&dummy58_handler,
	(uint32_t)&dummy59_handler,
	(uint32_t)&dummy60_handler,
	0,//(uint32_t)&dummy61_handler,
	0,//(uint32_t)&dummy62_handler,
	(uint32_t)&dummy63_handler,
	(uint32_t)&dummy64_handler,
	(uint32_t)&dummy65_handler,
	(uint32_t)&dummy66_handler,
	(uint32_t)&dummy67_handler,
	(uint32_t)&dummy68_handler,
	(uint32_t)&dummy69_handler,
	(uint32_t)&dummy70_handler,
	(uint32_t)&dummy71_handler,
	(uint32_t)&dummy72_handler,
	(uint32_t)&dummy73_handler,
	(uint32_t)&dummy74_handler,
	(uint32_t)&dummy75_handler,
	(uint32_t)&dummy76_handler,
	(uint32_t)&dummy77_handler,
	(uint32_t)&dummy78_handler,
	0,//(uint32_t)&dummy79_handler,
	0,//(uint32_t)&dummy80_handler,
	(uint32_t)&dummy81_handler,
	0,//(uint32_t)&dummy82_handler,
	0,//(uint32_t)&dummy83_handler,
	(uint32_t)&dummy84_handler,
	0,//(uint32_t)&dummy85_handler,
	0,//(uint32_t)&dummy86_handler,
	(uint32_t)&dummy87_handler,
	0,//(uint32_t)&dummy88_handler,
	0,//(uint32_t)&dummy89_handler,
	0,//(uint32_t)&dummy90_handler,
	(uint32_t)&dummy91_handler,
	(uint32_t)&dummy92_handler,
	(uint32_t)&dummy93_handler,
	(uint32_t)&dummy94_handler,
	(uint32_t)&dummy95_handler,
	(uint32_t)&dummy96_handler
	#endif
};

void Reset_Handler() {
	//copy .data section from flash to SRAM
	uint32_t size = (uint32_t)&__edata - (uint32_t)&__sdata;

	uint8_t *pSrc = (uint8_t*)&__la_data;//instead of __etext as there are other sections between .text and .data now
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