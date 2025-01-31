
#pragma once
#include <hardware/uart.h>

const uint8_t kRxBuffLengthPow = 7;
const uint8_t kTxBuffLengthPow = 7;
const uint16_t kRxBuffLength = 1 << (kRxBuffLengthPow);
const uint16_t kTxBuffLength = 1 << (kTxBuffLengthPow);

class DmaUart {
 private:
  uart_inst_t* uart_;

  __attribute__((aligned(kRxBuffLength)))
  uint8_t rx_buffer_[kRxBuffLength];
  uint16_t rx_user_index_; // next index to read
  uint16_t rx_dma_index_;  // next index dma will write

  __attribute__((aligned(kTxBuffLength)))
  uint8_t tx_buffer_[kTxBuffLength];
  uint16_t tx_user_index_;  // next index to write
  uint16_t tx_dma_index_;  // next index dma will read 

 public:
  DmaUart(uart_inst_t* uart, uint baudrate, int rx_gpio, int tx_gpio);
  uint16_t write(const uint8_t* data, uint16_t length);
  void flush();
  void write_and_flush(const uint8_t* data, uint16_t length);
  uint16_t read_byte(uint8_t* data);
  uint16_t read(uint8_t* data, uint16_t length);
  uint16_t read_all(uint8_t* data);
  
 private:
  void init_uart(uart_inst_t* uart, uint baudrate, int rx_gpio, int tx_gpio);
  void init_dma();
};
