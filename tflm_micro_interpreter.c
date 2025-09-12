#include "tflm_micro_interpreter.h"
#include <stdlib.h>

void tflm_setup() {}

void tflm_run_inference(int8_t* input, int8_t* output, int in_size, int out_size) {
    for (int i=0;i<out_size;i++) output[i] = rand() % 100;
}
