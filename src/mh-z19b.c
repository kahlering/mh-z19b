#include <stdint.h>
#include "mh-z19b.h"

#define RESP_TIMEOUT_MS 50

static const uint8_t read_co2_req[] = {0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
static const uint8_t zero_point_calibration_req[] = {0xff, 0x01, 0x87, 0x00, 0x0, 0x0, 0x0, 0x0, 0x78};
static const uint8_t enable_automatic_baseline_correction_req[] = {0xff, 0x01, 0x79, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xe6};
static const uint8_t disable_automatic_baseline_correction_req[] = {0xff, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86};
static uint8_t span_point_calibration_req[] = {0xff, 0x01, 0x88, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
static const uint8_t set_sensor_detection_range_2000_req[] = {0xff, 0x01, 0x99, 0x07, 0xD0, 0x0, 0x0, 0x0, 0x8f};
static const uint8_t set_sensor_detection_range_5000_req[] = {0xff, 0x01, 0x99, 0x13, 0x88, 0x0, 0x0, 0x0, 0xcb};
static const uint8_t get_sensor_detection_range_req[] = {0xff, 0x01, 0x9b, 0x0, 0x0, 0x0, 0x0, 0x0, 0x64};
static const uint8_t get_abc_status[] = {0xff, 0x01, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82};

static uart_tx_f_t uart_write_f;
static uart_rx_f_t uart_read_f;
static uart_discard_input_f_t uart_discard_input_f;

static uint8_t rx_buffer[16];

static uint8_t checksum(const uint8_t* const p){
    uint8_t checksum = 0;
    for(int i = 1; i < 8; ++i){
        checksum += p[i];
    }
    checksum = ~checksum;
    return checksum + 1;
}


int mh_z19b_get_c02_ppm(void){
    uart_discard_input_f();
    uart_write_f(read_co2_req, sizeof(read_co2_req));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x86 || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    
    return rx_buffer[2] * 256 + rx_buffer[3];
}

int mh_z19b_zero_point_calibration(void){
    uart_discard_input_f();
    uart_write_f(zero_point_calibration_req, sizeof(zero_point_calibration_req));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x87 || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    return 0;
}

int mh_z19b_span_point_calibration(const unsigned int ppm){
    span_point_calibration_req[3] = ppm / 256;
    span_point_calibration_req[4] = 0xff & ppm;
    span_point_calibration_req[8] = checksum(span_point_calibration_req);
    uart_write_f(span_point_calibration_req, sizeof(span_point_calibration_req));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x88 || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    return 0;
}

int mh_z19b_enable_abc(void){
    uart_discard_input_f();
    uart_write_f(enable_automatic_baseline_correction_req, sizeof(enable_automatic_baseline_correction_req));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x79 || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    
    return 0;
}

int mh_z19b_disable_abc(void){
    uart_discard_input_f();
    uart_write_f(disable_automatic_baseline_correction_req, sizeof(disable_automatic_baseline_correction_req));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x79 || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    return 0;
}

int mh_z19b_set_detection_range_2000ppm(void){
    uart_discard_input_f();
    uart_write_f(set_sensor_detection_range_2000_req, sizeof(set_sensor_detection_range_2000_req));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x99 || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    return 0;
}

int mh_z19b_set_detection_range_5000ppm(void){
    uart_discard_input_f();
    uart_write_f(set_sensor_detection_range_5000_req, sizeof(set_sensor_detection_range_5000_req));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x99 || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    return 0;
}

int mh_z19b_get_detection_range(void){
    uart_discard_input_f();
    uart_write_f(get_sensor_detection_range_req, sizeof(get_sensor_detection_range_req));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x9b || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    if(rx_buffer[2] == 5000 % 256){
        return 5000;
    }
    if(rx_buffer[2] == 2000 % 256){
        return 2000;
    }
    return -1;
}

int mh_z19b_get_abc_status(void){
    uart_discard_input_f();
    uart_write_f(get_abc_status, sizeof(get_abc_status));
    int bytes_recv = uart_read_f(rx_buffer, 9, RESP_TIMEOUT_MS);
    if(bytes_recv != 9){
        return -1;
    }
    if(rx_buffer[0] != 0xff || rx_buffer[1] != 0x7D || rx_buffer[8] != checksum(rx_buffer)){
        return -1;
    }
    
    return rx_buffer[7];
}

void mh_z19b_init(const uart_rx_f_t _uart_rx_f, const uart_tx_f_t _uart_tx_f, const uart_discard_input_f_t _uart_discard_input_f){
    uart_write_f = _uart_tx_f;
    uart_read_f = _uart_rx_f;
    uart_discard_input_f = _uart_discard_input_f;
}
