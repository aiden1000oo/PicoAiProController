#include "tusb.h"
#include <string.h>

tusb_desc_device_t const desc_device =
{
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor           = 0x057E, // Nintendo
    .idProduct          = 0x2009, // Pro Controller
    .bcdDevice          = 0x0100,

    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,

    .bNumConfigurations = 0x01
};

uint8_t const * tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

// Simplified Pro Controller HID descriptor: 16 buttons, hat, 4 axes
uint8_t const desc_hid_report[] = {
  0x05, 0x01,       // Usage Page (Generic Desktop)
  0x09, 0x05,       // Usage (Game Pad)
  0xA1, 0x01,       // Collection (Application)
  0x15, 0x00,       //   Logical Minimum (0)
  0x25, 0x01,       //   Logical Maximum (1)
  0x35, 0x00,       //   Physical Minimum (0)
  0x45, 0x01,       //   Physical Maximum (1)
  0x75, 0x01,       //   Report Size (1)
  0x95, 0x10,       //   Report Count (16 buttons)
  0x05, 0x09,       //   Usage Page (Button)
  0x19, 0x01,       //   Usage Minimum (Button 1)
  0x29, 0x10,       //   Usage Maximum (Button 16)
  0x81, 0x02,       //   Input (Data,Var,Abs)
  0x05, 0x01,       //   Usage Page (Generic Desktop)
  0x25, 0x07,       //   Logical Maximum (7)
  0x46, 0x3B, 0x01, //   Physical Maximum (315)
  0x75, 0x04,       //   Report Size (4)
  0x95, 0x01,       //   Report Count (1)
  0x65, 0x14,       //   Unit (Eng Rot: Degrees)
  0x09, 0x39,       //   Usage (Hat switch)
  0x81, 0x42,       //   Input (Data,Var,Abs,Null)
  0x65, 0x00,       //   Unit (None)
  0x95, 0x01,       //   Report Count (1)
  0x75, 0x04,       //   Report Size (4)
  0x81, 0x03,       //   Input (Const,Var,Abs)
  0x05, 0x01,       //   Usage Page (Generic Desktop)
  0x09, 0x30,       //   Usage (X)
  0x09, 0x31,       //   Usage (Y)
  0x09, 0x32,       //   Usage (Z)
  0x09, 0x35,       //   Usage (Rz)
  0x15, 0x00,       //   Logical Minimum (0)
  0x26, 0xFF, 0x00, //   Logical Maximum (255)
  0x75, 0x08,       //   Report Size (8)
  0x95, 0x04,       //   Report Count (4 axes)
  0x81, 0x02,       //   Input (Data,Var,Abs)
  0xC0              // End Collection
};

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance) {
    (void)instance;
    return desc_hid_report;
}

enum {
    ITF_NUM_HID,
    ITF_NUM_TOTAL
};

#define CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

uint8_t const desc_configuration[] = {
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),
    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_NONE,
                       sizeof(desc_hid_report), 0x81, 16, 10)
};

uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    (void) index;
    return desc_configuration;
}

char const* string_desc_arr[] = {
    (const char[]) {0x09, 0x04},
    "Nintendo Co., Ltd.",
    "Pro Controller",
    "00000001",
};

static uint16_t _desc_str[32];
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void) langid;
    uint8_t chr_count;

    if (index == 0) {
        _desc_str[1] = (0x0409);
        _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 + 2);
        return _desc_str;
    }

    const char* str = string_desc_arr[index];
    chr_count = strlen(str);
    if (chr_count > 31) chr_count = 31;

    for (uint8_t i = 0; i < chr_count; i++) {
        _desc_str[1+i] = str[i];
    }
    _desc_str[0] = (TUSB_DESC_STRING << 8) | (2*chr_count + 2);
    return _desc_str;
}
