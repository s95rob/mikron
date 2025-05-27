#pragma once

static inline void arm_memory_barrier() {
    //asm volatile("dmb" ::: "memory");
}

static inline void arm_sync_barrier() {
    //asm volatile("dsb" ::: "memory");
}

static inline void arm_delay(uint32_t cycles) {
	asm volatile("__delay_%=: subs %[cycles], %[cycles], #1; bne __delay_%=\n"
		 : "=r"(cycles): [cycles]"0"(cycles) : "cc");
}