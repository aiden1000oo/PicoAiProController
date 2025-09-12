#include "tflm_micro_interpreter.h"
#include <stdlib.h>

void tflm_setup() {
    // Normally initialize interpreter with g_model_data
}

void tflm_run_inference(int8_t* input, int8_t* output, int in_size, int out_size) {
    // Stub inference: random values
    for (int i=0;i<out_size;i++) output[i] = rand() % 100;
}
