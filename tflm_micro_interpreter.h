#ifndef TFLM_MICRO_INTERPRETER_H
#define TFLM_MICRO_INTERPRETER_H
#include <stdint.h>

void tflm_setup();
void tflm_run_inference(int8_t* input, int8_t* output, int in_size, int out_size);

#endif
