#include "spi.h"

#define ch3		(0x03<<25)
#define AF05  (0x05)

/**

	* @brief initialize SPI1 peripheral and required pins
  * @param  None
  * @retval None		
		
*/
/*void spi1_init(void)
		{
			//enable clock for GPIOA
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN; 
			//set PA5, PA6 and PA7 to alternate function mode
		GPIOA->MODER|=GPIO_MODER_MODE5_1|GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1; 
			//set which type of alternate function is
		GPIOA->AFR[0]|=(AF05<<20)|(AF05<<24)|(AF05<<28);
			//enable clock access to SPI1
		RCC->APB2ENR|=RCC_APB2ENR_SPI1EN;
			//set software slave managment
		SPI1->CR1|=SPI_CR1_SSM|SPI_CR1_SSI;
			//set SPI in master mode
		SPI1->CR1|=SPI_CR1_MSTR;
		SPI1->CR1|=SPI_CR1_BR_0|SPI_CR1_CPHA|SPI_CR1_CPOL;
			//enable DMA_TX DMA_RX buffer
		SPI1->CR2|=SPI_CR2_TXDMAEN|SPI_CR2_RXDMAEN;
			//enable SPI peripheral
		SPI1->CR1|=SPI_CR1_SPE;
		
		
		}*/

/**

	* @brief intialize DMA2 Stream3 Channel 3
  * @param  None
  * @retval None		
		
*/
		//SPI_TX
void dma2_stream3_ch3_init(void)
	{
	RCC->AHB1ENR|=RCC_AHB1ENR_DMA2EN;
	DMA2_Stream3->CR&=~DMA_SxCR_EN;
	while((DMA2_Stream3->CR)&DMA_SxCR_EN){;}
	DMA2_Stream3->CR=ch3|DMA_SxCR_MINC|DMA_SxCR_DIR_0|DMA_SxCR_TCIE
	|DMA_SxCR_HTIE|DMA_SxCR_TEIE|DMA_SxCR_DMEIE;
	DMA2_Stream3->FCR |= DMA_SxFCR_DMDIS;
  DMA2_Stream3->FCR |= (DMA_SxFCR_FTH_0 | DMA_SxFCR_FTH_1);
	
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	
	}
	
	//SPI_RX
	void dma2_stream2_ch3_init(void)
	{
	RCC->AHB1ENR|=RCC_AHB1ENR_DMA2EN;
	DMA2_Stream2->CR&=~DMA_SxCR_EN;
	while((DMA2_Stream2->CR)&DMA_SxCR_EN){;}
	DMA2_Stream2->CR=ch3|DMA_SxCR_MINC|DMA_SxCR_TCIE
	|DMA_SxCR_HTIE|DMA_SxCR_TEIE|DMA_SxCR_DMEIE;
	DMA2_Stream2->FCR |= DMA_SxFCR_DMDIS;
  DMA2_Stream2->FCR |= (DMA_SxFCR_FTH_0 | DMA_SxFCR_FTH_1);
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	
	}
	
	/**
	* @brief initiation DMA transfer
  * @param  uint32_t src for data source 
	* @param  uint32_t length of data source 	
  * @retval None		
		
*/
	
	void spi_transfer_dma(uint32_t src,uint32_t len)
			{
				DMA2->LIFCR |=DMA_LIFCR_CTCIF3|DMA_LIFCR_CHTIF3|DMA_LIFCR_CTEIF3|DMA_LIFCR_CDMEIF3|DMA_LIFCR_CFEIF3;
			
				DMA2_Stream3->PAR= (uint32_t)&(SPI1->TXDR);
				DMA2_Stream3->M0AR=src;
				DMA2_Stream3->NDTR=len;
				
				DMA2_Stream3->CR|=DMA_SxCR_EN;
			}

	void spi_receive_dma (uint32_t dest,uint32_t len)
				{
				DMA2->LIFCR |=DMA_LIFCR_CTCIF2|DMA_LIFCR_CHTIF2|DMA_LIFCR_CTEIF2|DMA_LIFCR_CDMEIF2|DMA_LIFCR_CFEIF2;
				
				DMA2_Stream2->PAR= (uint32_t)&(SPI1->RXDR);
				DMA2_Stream2->M0AR=dest;
				DMA2_Stream2->NDTR=len;
				DMA2_Stream2->CR|=DMA_SxCR_EN;
				}
