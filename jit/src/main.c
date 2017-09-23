#include <stdio.h>
#include <lightning.h>

typedef int (*pifv)(void);

static jit_state_t *_jit;

int main(int argc, char *argv[]) {
	pifv program;
	jit_node_t *label_a, *label_b, *label_c, *label_main;
	jit_node_t *call_a, *call_b;

	init_jit(argv[0]);

	_jit = jit_new_state();

	label_a = jit_label();
	jit_prolog();
	jit_prepare();
	call_b = jit_finishi(NULL);
	jit_retval(JIT_R0);
	jit_retr(JIT_R0);
	jit_epilog();

	label_b = jit_label();
	jit_prolog();
	jit_reti(9);
	jit_epilog();

	label_main = jit_note(__FILE__, __LINE__);
	label_c = jit_label();
	jit_prolog();
	jit_prepare();
	call_a = jit_finishi(NULL);
	jit_retval(JIT_R0);
	jit_retr(JIT_R0);
	jit_epilog();

	jit_patch_at(call_a, label_a);
	jit_patch_at(call_b, label_b);
	jit_emit();

	program = (pifv) jit_address(label_main);
	jit_clear_state();
	printf("result = %d\n", program());
	jit_destroy_state();
	finish_jit();
	return (0);
}
