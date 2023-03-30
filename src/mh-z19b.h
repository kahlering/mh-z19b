#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef int (*uart_rx_f_t)(uint8_t* buf, const int len, const int time_out_ms);
typedef int (*uart_tx_f_t)(const uint8_t* buf, const int len);
typedef void (*uart_discard_input_f_t)();

/**
 * @brief read the co2 concentration as ppm
 * 
 * @return int success: co2 ppm   failure: -1
 */
int mh_z19b_get_c02_ppm(void);

/**
 * @brief calibrate the sensor assuming that the current concentration is 400 ppm.
 * 
 * @return int success: 0    failure: -1 
 */
int mh_z19b_zero_point_calibration(void);

/**
 * @brief please do a zero point calibration before span point calibration.
 * 
 * @param ppm the current co2 concentration
 * @return int success: 0    failure: -1 
 */
int mh_z19b_span_point_calibration(const unsigned int ppm);

/**
 * @brief disables the automatic baseline correction. 
 * 
 * @return int success: 0    failure: -1 
 */
int mh_z19b_disable_abc(void);

/**
 * @brief enabled the automatic baseline correction
 * 
 * @return int success: 0    failure: -1 
 */
int mh_z19b_enable_abc(void);

/**
 * @brief read automatic baseline status
 * 
 * @return int abc enabled: 1    abs disabled: 0    failure: -1
 */
int mh_z19b_get_abc_status(void);

/**
 * @brief set the detection range to 2000ppm
 * 
 * @return int success: 0    failure: -1 
 */
int mh_z19b_set_detection_range_2000ppm(void);

/**
 * @brief set the detection_range t0 5000ppm
 * 
 * @return int success: 0    failure: -1
 */
int mh_z19b_set_detection_range_5000ppm(void);

/**
 * @brief read the current detection range
 * 
 * @return int success: current range    failure: -1
 */
int mh_z19b_get_detection_range();

/**
 * @brief initialise the library
 * 
 * @param uart_rx_f callback to read from the uart
 * @param uart_tx_f callback to write to the uart
 * @param uart_discard_input_f callback to discard the uart input
 */
void mh_z19b_init(const uart_rx_f_t uart_rx_f, const uart_tx_f_t uart_tx_f, const uart_discard_input_f_t uart_discard_input_f);


#ifdef __cplusplus
}
#endif
