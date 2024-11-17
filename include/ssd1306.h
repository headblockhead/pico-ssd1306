#pragma once

#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdint.h>

typedef enum {
  SET_CONTRAST = 0x81,
  SET_ENTIRE_ON = 0xA4,
  SET_NORM_INV = 0xA6,
  SET_DISP = 0xAE,
  SET_MEM_ADDR = 0x20,
  SET_COL_ADDR = 0x21,
  SET_PAGE_ADDR = 0x22,
  SET_DISP_START_LINE = 0x40,
  SET_SEG_REMAP = 0xA0,
  SET_MUX_RATIO = 0xA8,
  SET_COM_OUT_DIR = 0xC0,
  SET_DISP_OFFSET = 0xD3,
  SET_COM_PIN_CFG = 0xDA,
  SET_DISP_CLK_DIV = 0xD5,
  SET_PRECHARGE = 0xD9,
  SET_VCOM_DESEL = 0xDB,
  SET_CHARGE_PUMP = 0x8D
} ssd1306_command_t;

typedef enum {
  ROT_0 = 0,
  ROT_90 = 1,
  ROT_180 = 2,
  ROT_270 = 3,
} ssd1306_rotation_t;

typedef struct {
  uint8_t width;
  uint8_t height;
  uint8_t pages;
  uint8_t address;
  i2c_inst_t *i2c_i;
  bool external_vcc;
  uint8_t *buffer;
  size_t bufsize;
  ssd1306_rotation_t rotation;
} ssd1306_t;

int ssd1306_init(ssd1306_t *p, uint16_t width, uint16_t height, uint8_t address,
                 i2c_inst_t *i2c_instance);

void ssd1306_deinit(ssd1306_t *p);

void ssd1306_poweroff(ssd1306_t *p);

void ssd1306_poweron(ssd1306_t *p);

void ssd1306_contrast(ssd1306_t *p, uint8_t val);

void ssd1306_invert(ssd1306_t *p, uint8_t inv);

void ssd1306_show(ssd1306_t *p);

void ssd1306_clear(ssd1306_t *p);

void ssd1306_set_rotation(ssd1306_t *p, ssd1306_rotation_t rotation);

void ssd1306_clear_pixel(ssd1306_t *p, uint32_t x, uint32_t y);

void ssd1306_draw_pixel(ssd1306_t *p, uint32_t x, uint32_t y);

void ssd1306_draw_line(ssd1306_t *p, int32_t x1, int32_t y1, int32_t x2,
                       int32_t y2);

void ssd1306_clear_square(ssd1306_t *p, uint32_t x, uint32_t y, uint32_t width,
                          uint32_t height);

void ssd1306_draw_square(ssd1306_t *p, uint32_t x, uint32_t y, uint32_t width,
                         uint32_t height);

void ssd1306_draw_empty_square(ssd1306_t *p, uint32_t x, uint32_t y,
                               uint32_t width, uint32_t height);

void ssd1306_bmp_show_image_with_offset(ssd1306_t *p, const uint8_t *data,
                                        const long size, uint32_t x_offset,
                                        uint32_t y_offset);

void ssd1306_bmp_show_image(ssd1306_t *p, const uint8_t *data, const long size);

void ssd1306_draw_char_with_font(ssd1306_t *p, uint32_t x, uint32_t y,
                                 uint32_t scale, const uint8_t *font, char c);

void ssd1306_draw_char(ssd1306_t *p, uint32_t x, uint32_t y, uint32_t scale,
                       char c);

void ssd1306_draw_string_with_font(ssd1306_t *p, uint32_t x, uint32_t y,
                                   uint32_t scale, const uint8_t *font,
                                   const char *s);

void ssd1306_draw_string(ssd1306_t *p, uint32_t x, uint32_t y, uint32_t scale,
                         const char *s);
