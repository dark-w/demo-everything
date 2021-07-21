#pragma once

enum lignting_effects {
    gradual_change_plus,
    single_monochrome_running,
};

/*
* HSV color model, it can be interconverted with rgb color model.
*
* H: Hue
* S: Saturation
* V: Value
*/
struct hsv_float_value {
    float h;
    float s;
    float v;
};

struct rgb_float_value {
    float r;
    float g;
    float b;
};

/*
* brief: this is the base struct of all parameters structure, do not use it, pls see the source
*   code about how important it is.
*/
struct rgb_le_param_base {
    char dummy;
};

// single_monochrome_running
struct rgb_le_param_smr {
    struct hsv_float_value hsv;
    unsigned char speed;

    struct rgb_le_param_base base;
};

// gradual_change_plus
struct rgb_le_param_gcp {
    unsigned char speed;

    struct rgb_le_param_base base;
};

/*
* user interface 1
*/
void app_rgb_ws2812_init(enum lignting_effects le,
                         struct rgb_le_param_base *param);

/*
* user interface 2
*/
void app_rgb_ws2812_lighting_effects();

/*
* user tool interface
*/
void rgb_to_hsv(struct rgb_float_value rgb, struct hsv_float_value *hsv);
void hsv_to_rgb(struct hsv_float_value hsv, struct rgb_float_value *rgb);

#define NUMBER_OF_COLOR (3)
#define NUMBER_OF_RESET_CYCLE (20)

/*
* configuration
* 
* notice that the number_of_rgb must equal to NUMBER_OF_RGB!
*/
#define NUMBER_OF_RGB 11

/*
* you gotta provide these variables in your user file which is base on librgb.a
* notice that the dimension must equal to the number_of_rbg + NUMBER_OF_RESET_CYCLE.
* now, you can put the macro 'LIBRGB_SUPPORTED' in your user file, that's instead of
* all.
*/
extern const unsigned char
    number_of_rbg; // you can set the value in this range: [10, +∞)

extern unsigned short pwm_data_dma[][NUMBER_OF_COLOR][8 * 2];
extern unsigned char h_flag_array[];
extern struct hsv_float_value hsv_float_value_array[];

#define LIBRGB_SUPPORTED(x)                                                    \
    const unsigned char number_of_rbg = x;                                     \
    unsigned short pwm_data_dma[x + NUMBER_OF_RESET_CYCLE][NUMBER_OF_COLOR]    \
                               [8 * 2];                                        \
    unsigned char h_flag_array[x + NUMBER_OF_RESET_CYCLE];                     \
    struct hsv_float_value hsv_float_value_array[x + NUMBER_OF_RESET_CYCLE];

/*
* can be used for your pwm pheripheral initialization.
*
* usage:
*       pwm_ch0.load = PWM_DMA_PAYLOAD;
*       ...
*       pwm_ch0.xfer_len = PWM_DMA_XFER_LEN;
*       ...
*       pwm_ch0.pcmp = PWM_DMA_DATA_ARRAY;
*/
#define PWM_DMA_PAYLOAD (9)
#define PWM_DMA_XFER_LEN ((number_of_rbg + NUMBER_OF_RESET_CYCLE) * 24)
#define PWM_DMA_DATA_ARRAY ((uint16_t *)pwm_data_dma)

#define __RAM_FUNC
