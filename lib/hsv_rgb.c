#include "hsv_rgb.h"

#define container_of(ptr, type, mem)                                           \
    (type *)((char *)ptr - (unsigned long)(&((type *)0)->mem))

#define RESET_CYCLE (32)

enum lignting_effects le_global;

// unsigned short pwm_data_dma[NUMBER_OF_RBG + NUMBER_OF_RESET_CYCLE][NUMBER_OF_COLOR][8 * 2];

/* brief: reverting the rgb value (like 255) to the pwm value array.
* param:
*      1. value: ...
*      2. pwm_value_array: ...
*      3. reset: if the 'reset' is 1 that mean's the function will setting the 'reset cycle',
*                normally the value is 'pwm payload'. if the 'reset' is 0, the function
*                just setting pwm value base on rgb value.
*/
__RAM_FUNC static void __rgb_value_revert_to_pwm_value(
    unsigned char value, unsigned short *pwm_value_array, unsigned char reset)
{
    if (reset) {
        for (unsigned char i = 0; i < 8; i++)
            pwm_value_array[(8 - 1 - i) * 2] = PWM_DMA_PAYLOAD;
    } else {
        for (unsigned char i = 0; i < 8; i++) {
            if (value & (1 << i))
                pwm_value_array[(8 - 1 - i) * 2] = PWM_DMA_PAYLOAD - 7;
            else
                pwm_value_array[(8 - 1 - i) * 2] = PWM_DMA_PAYLOAD - 3;
        }
    }
}

__RAM_FUNC static void __rbg_set_single(unsigned char g, unsigned char r,
                                        unsigned char b,
                                        unsigned short pwm_value_array[][8 * 2])
{
    __rgb_value_revert_to_pwm_value(g, pwm_value_array[0], 0);
    __rgb_value_revert_to_pwm_value(r, pwm_value_array[1], 0);
    __rgb_value_revert_to_pwm_value(b, pwm_value_array[2], 0);
}

static void __rgb_data_init()
{
    unsigned char i;
    for (i = 0; i < number_of_rbg; i++)
        __rbg_set_single(0, 0, 0, pwm_data_dma[i]);

    // reset cycle init
    for (; i < number_of_rbg + NUMBER_OF_RESET_CYCLE; i++)
        for (unsigned char j = 0; j < NUMBER_OF_COLOR; j++)
            __rgb_value_revert_to_pwm_value(0, pwm_data_dma[i][j], 1);
}

static inline float __retmax(float a, float b, float c)
{
    float max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;

    return max;
}

static inline float __retmin(float a, float b, float c)
{
    float min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;

    return min;
}

void rgb_to_hsv(struct rgb_float_value rgb, struct hsv_float_value *hsv)
{
    float max = 0, min = 0;
    float R = rgb.r / 255;
    float G = rgb.g / 255;
    float B = rgb.b / 255;

    max = __retmax(R, G, B);
    min = __retmin(R, G, B);
    hsv->v = max;
    if (max == 0)
        hsv->s = 0;
    else
        hsv->s = 1 - (min / max);

    if (max == min)
        hsv->h = 0;
    else if (max == R && G >= B)
        hsv->h = 60 * ((G - B) / (max - min));
    else if (max == R && G < B)
        hsv->h = 60 * ((G - B) / (max - min)) + 360;
    else if (max == G)
        hsv->h = 60 * ((B - R) / (max - min)) + 120;
    else if (max == B)
        hsv->h = 60 * ((R - G) / (max - min)) + 240;

    hsv->v = hsv->v * 100;
    hsv->s = hsv->s * 100;
}

void hsv_to_rgb(struct hsv_float_value hsv, struct rgb_float_value *rgb)
{
    float C = 0, X = 0, Y = 0, Z = 0;
    int i = 0;
    float H = (float)(hsv.h);
    float S = (float)(hsv.s) / 100.0;
    float V = (float)(hsv.v) / 100.0;
    if (S == 0)
        rgb->r = rgb->g = rgb->b = V;
    else {
        H = H / 60;
        i = (int)H;
        C = H - i;

        X = V * (1 - S);
        Y = V * (1 - S * C);
        Z = V * (1 - S * (1 - C));
        switch (i) {
        case 0:
            rgb->r = V;
            rgb->g = Z;
            rgb->b = X;
            break;
        case 1:
            rgb->r = Y;
            rgb->g = V;
            rgb->b = X;
            break;
        case 2:
            rgb->r = X;
            rgb->g = V;
            rgb->b = Z;
            break;
        case 3:
            rgb->r = X;
            rgb->g = Y;
            rgb->b = V;
            break;
        case 4:
            rgb->r = Z;
            rgb->g = X;
            rgb->b = V;
            break;
        case 5:
            rgb->r = V;
            rgb->g = X;
            rgb->b = Y;
            break;

        default:
            rgb->r = 0;
            rgb->g = 0;
            rgb->b = 0;
        }
    }
    rgb->r = rgb->r * 255;
    rgb->g = rgb->g * 255;
    rgb->b = rgb->b * 255;
}

static struct rgb_le_param_gcp param_gcp;

static void
__rgb_hsv_test_gradual_change_plus_init(struct rgb_le_param_base *param)
{
    struct rgb_le_param_gcp *p_param =
        container_of(param, struct rgb_le_param_gcp, base);

    param_gcp.speed = p_param->speed;

    for (unsigned char i = 0; i < number_of_rbg; i++) {
        hsv_float_value_array[i].s = 100;
        hsv_float_value_array[i].v = 100;
        hsv_float_value_array[i].h = i * (240 / number_of_rbg / 1);

        h_flag_array[i] = 1;
    }
}

static void __rgb_hsv_test_gradual_change_plus()
{
    static unsigned int tick = 0;

    tick++;
    if (param_gcp.speed == tick) {
        for (unsigned char index = 0; index < number_of_rbg; index++) {
            if (hsv_float_value_array[index].h >= 230)
                h_flag_array[index] = 0;
            else if (hsv_float_value_array[index].h <= 5)
                h_flag_array[index] = 1;

            if (h_flag_array[index])
                hsv_float_value_array[index].h++;
            else
                hsv_float_value_array[index].h--;

            struct rgb_float_value rgb_float_value;
            hsv_to_rgb(hsv_float_value_array[index], &rgb_float_value);

            __rbg_set_single((unsigned char)rgb_float_value.g,
                             (unsigned char)rgb_float_value.r,
                             (unsigned char)rgb_float_value.b,
                             pwm_data_dma[index]);
        }

        tick = 0;
    }
}

struct rgb_le_param_smr param_smr;

static void __rgb_ws2812_le_smr_init(struct rgb_le_param_base *param)
{
    for (unsigned char index = 0; index < number_of_rbg; index++) {
        __rbg_set_single(0, 0, 255, pwm_data_dma[index]);
    }
}

__RAM_FUNC static void __rgb_ws2812_le_smr()
{
    static unsigned int count = 0;

    count++;
    if (param_smr.speed == count) {
        for (unsigned char index = 0; index < number_of_rbg; index++) {
            __rbg_set_single(0, 0, 255, pwm_data_dma[index]);
        }

        count = 0;
    }
}

void app_rgb_ws2812_init(enum lignting_effects le,
                         struct rgb_le_param_base *param)
{
    __rgb_data_init();

    le_global = le;

    switch (le_global) {
    case gradual_change_plus:
        /* code */
        __rgb_hsv_test_gradual_change_plus_init(param);
        break;

    case single_monochrome_running:
        __rgb_ws2812_le_smr_init(param);
        break;

    default:
        break;
    }
}

__RAM_FUNC void app_rgb_ws2812_lighting_effects()
{
    switch (le_global) {
    case gradual_change_plus:
        /* code */
        __rgb_hsv_test_gradual_change_plus();
        break;

    case single_monochrome_running:
        __rgb_ws2812_le_smr();
        break;

    default:
        break;
    }
}
