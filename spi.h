#ifndef __spi__h

#define __spi__h
#include "stm32h7xx.h"                  // Device header


void spi1_init(void);

void dma2_stream3_ch3_init(void);
void dma2_stream2_ch3_init(void);
void spi_transfer_dma(uint32_t src,uint32_t len);
void spi_receive_dma (uint32_t dest,uint32_t len);


#endif
