#include <assert.h>
#include <stdio.h>
#include <lightning.h>

typedef int (*pvfi)();

int main(int argc, char *argv[]) {
	int n = 0, m = 0;
	int m_size = 32;
	int size = m_size * 1024;
	init_jit(0);
	jit_node_t* fs[size];
	pvfi funcs[size];
	jit_state_t* _jit = jit_new_state();
	for (n = 0; n < m_size; n++) {
		for (m = 0; m < 1024; m++) {
			fs[n * m_size + m] = jit_note(0, 0);
			jit_prolog();
			jit_movi(JIT_R0, 1234);
			jit_retr(JIT_R0);
			jit_epilog();
		}
	}
	jit_emit();
	for (n = 0; n < m_size; n++) {
		for (m = 0; m < 1024; m++) {
			jit_node_t* f = fs[n * m_size + m];
			funcs[n * m_size + m] = (pvfi) jit_address(f);
		}
	}
	jit_clear_state();
	finish_jit();
	for (n = 0; n < m_size; n++) {
		for (m = 0; m < 1024; m++) {
			assert(funcs[n * m_size + m]() == 1234);
		}
	}
	sleep(5);
	jit_destroy_state();
	sleep(10);
	return 0;
}
