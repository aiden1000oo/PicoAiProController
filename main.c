#include "pico/stdlib.h"
#include "tusb.h"
#include "model_data.h"
#include "tflm_micro_interpreter.h"

typedef struct {
    uint16_t buttons;
    uint8_t  hat;
    uint8_t  lx, ly;
    uint8_t  rx, ry;
} __attribute__((packed)) switch_report_t;

static uint32_t ai_timer = 0;

void ai_controller_task(void) {
    if (!tud_hid_ready()) return;
    switch_report_t rpt = {0};

    ai_timer++;
    if (ai_timer % 100 == 0) {
        int8_t input[2] = { (int8_t)(ai_timer & 0xFF), (int8_t)(rand() & 0xFF) };
        int8_t output[3];
        tflm_run_inference(input, output, 2, 3);

        int choice = 0;
        int maxv = output[0];
        for (int i=1;i<3;i++) if (output[i] > maxv) { choice = i; maxv = output[i]; }

        if (choice == 0) {
            rpt.buttons |= (1 << 0); // A button
            rpt.lx = 0xFF; rpt.ly = 0x80;
        } else if (choice == 1) {
            rpt.buttons |= (1 << 1); // B button
            rpt.ly = 0x00; // jump-ish
        } else {
            rpt.hat = GAMEPAD_HAT_DOWN; // taunt
        }
    }

    tud_hid_report(0, &rpt, sizeof(rpt));
}

int main() {
    stdio_init_all();
    tusb_init();
    tflm_setup();
    while (1) {
        tud_task();
        ai_controller_task();
        sleep_ms(5);
    }
}

uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t* buffer, uint16_t reqlen) {
    (void) itf; (void) report_id; (void) report_type;
    (void) buffer; (void) reqlen;
    return 0;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const* buffer, uint16_t bufsize) {
    (void) itf; (void) report_id; (void) report_type;
    (void) buffer; (void) bufsize;
}
