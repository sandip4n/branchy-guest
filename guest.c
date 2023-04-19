#include <stddef.h>
#include <stdint.h>

/*
 * Loop with a million instructions
 * Based on https://github.com/deater/perf_event_tests/blob/master/lib/instructions_testcode.c
 */
static inline void
__attribute__((__always_inline__))
pmc_test_loop(void)
{
	asm volatile(
		"	xor	%%ecx,%%ecx\n"
		"	mov	$499999,%%ecx\n"
		"1:\n"
		"	dec	%%ecx\n"
		"	jnz	1b\n"
		:			/* no output registers */
		:			/* no inputs */
		: "cc", "%ecx"		/* clobbered */
	);
}

void
__attribute__((noreturn))
__attribute__((section(".start")))
_start(void) {
	int i;

	for (i = 0; i < 5000; i++)
		pmc_test_loop();

	*(long *) 0x400 = 42;
	for (;;)
		asm("hlt" : /* empty */ : "a" (42) : "memory");
}
