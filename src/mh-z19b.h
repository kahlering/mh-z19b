#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef int (*uart_rx_f_t)(uint8_t* buf, const int len, const int time_out_ms);
typedef int (*uart_tx_f_t)(const uint8_t* buf, const int len);
typedef void (*uart_discard_input_f_t)();

int mh_z19b_get_c02_ppm(void);

int mh_z19b_zero_point_calibration(void);

int mh_z19b_span_point_calibration(const unsigned int ppm);

int mh_z19b_disable_abc(void);

int mh_z19b_enable_abc(void);

int mh_z19b_get_abc_status(void);

int mh_z19b_set_detection_range_2000ppm(void);

int mh_z19b_set_detection_range_5000ppm(void);

int mh_z19b_get_detection_range();

void mh_z19b_init(const uart_rx_f_t uart_rx_f, const uart_tx_f_t uart_tx_f, const uart_discard_input_f_t uart_discard_input_f);


#ifdef __cplusplus
}
#endif
