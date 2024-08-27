/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

FDCAN_HandleTypeDef hfdcan1;

SPI_HandleTypeDef hspi3;
DMA_HandleTypeDef hdma_spi3_tx;
DMA_HandleTypeDef hdma_spi3_rx;

/* USER CODE BEGIN PV */
uint8_t SPI_resp[4]={0xAA,0xbb,0xcc,0xdd};

uint8_t SPI_RX[4]={0,0,0,0};
uint8_t RXCMD1[4]={0x10,0x00,0x00,0x0d};
uint8_t RXCMD2[4]={0x50,0x00,0x00,0xFC};
uint32_t ctr0=0;
uint32_t ctr2=0;
uint32_t ctr=0;


const uint32_t FRONT_100_50_X_transformed[261]={0x87f4c026,0x87f34004,0x87f000f6,0x87f4c026,0x87f000f6,0x87f000f6,0x87f000f6,0x87f4c026,0x87f34004,0x87f34004,0x87f000f6,0x87f4c026,0x87f000f6,0x87f34004,0x87f4c026,0x87f34004,0x87f34004,0x87f4c026,0x87f000f6,0x87f000f6,0x87f4c026,0x87f4c026,0x87f34004,0x87f000f6,0x87f4c026,0x87f000f6,0x87f000f6,0x87f34004,0x87f4c026,0x87f000f6,0x87f280e8,0x87f58029,0x87f34004,0x87f000f6,0x87f58029,0x87f34004,0x87f000f6,0x87f4c026,0x87f34004,0x87f000f6,0x87f000f6,0x87f000f6,0x87f4c026,0x87f000f6,0x87f34004,0x87f4c026,0x87f000f6,0x87f000f6,0x87f34004,0x87f000f6,0x87f000f6,0x87f34004,0x87f000f6,0x87f4c026,0x87f000f6,0x87f34004,0x87f000f6,0x87f34004,0x87f000f6,0x87f000f6,0x87f000f6,0x87f000f6,0x87f000f6,0x87f000f6,0x87f280e8,0x87f04010,0x87e440e0,0x87bbc0f6,0x87ea404d,0x87f70037,0x87d300a8,0x87e440e0,0x8422804c,0x87c880ff,0x87a88021,0x8422804c,0x87b48054,0x87950014,0x840b406f,0x87b18068,0x87b3c073,0x840d8042,0x87c28087,0x87b6004a,0x87f000f6,0x87704017,0x87e740f4,0x8509c07f,0x877d0048,0x877f4053,0x841800b8,0x8775802e,0x87b84001,0x849bc0ae,0x86be00c1,0x87458041,0x8421c0be,0x868540d9,0x87c00099,0x87d300a8,0x86c70056,0x849c8089,0x84e500fd,0x86d9c0db,0x8747005f,0x873980ea,0x878d8057,0x85408061,0x841200c0,0x86d54068,0x878fc04c,0x8740009e,0x87404078,0x87a00047,0x87cd0020,0x84ab8027,0x841ec095,0x87ad00fe,0x87c7c05d,0x875f00ff,0x876f8073,0x87db40cb,0x875900d7,0x87e740f4,0x87b3c073,0x870540d0,0x87b48054,0x87c3406b,0x87350059,0x87bf80c5,0x87fdc04a,0x87b0c067,0x846b0057,0x847d005a,0x874ac0e3,0x84f5803b,0x87e9805c,0x874f403c,0x8414400e,0x8771c01d,0x86d48084,0x84024003,0x86a6c064,0x86d78090,0x87464050,0x87d0c0b9,0x86eb004c,0x872e400b,0x874b80ec,0x8756c096,0x87e500ef,0x86b4405f,0x878b407a,0x841e0090,0x875300af,0x873980ea,0x87464050,0x875e40f0,0x87410077,0x877a0089,0x87af40e5,0x87350059,0x87a28059,0x87b24079,0x87c880ff,0x87d54066,0x879a40b6,0x87d840df,0x84000018,0x87b6c04f,0x87fdc04a,0x843c0027,0x87ad00fe,0x87df00f8,0x87ca00e1,0x8735c05c,0x87a64089,0x87a64089,0x87830019,0x87788097,0x87770030,0x8795c011,0x8798c0a8,0x877000f1,0x8769805b,0x875a8020,0x8766801f,0x879200d5,0x876f8073,0x877f4053,0x878d8057,0x87aac03a,0x87be00cf,0x87d54066,0x87af40e5,0x87da8027,0x87ca00e1,0x87a64089,0x87de40f7,0x87c64057,0x87de40f7,0x87cdc025,0x87dfc0fd,0x87d60094,0x87c58046,0x87b0c067,0x87cc00c9,0x87ea404d,0x87e68018,0x87d180b6,0x87db40cb,0x87fe80b8,0x87e5c0ea,0x87d6c091,0x87e08030,0x87e140dc,0x87fb8084,0x87fac08b,0x87ebc047,0x87df00f8,0x87ef8074,0x87f04010,0x87f1001f,0x87f280e8,0x87f58029,0x8400c01d,0x8408407b,0x87f7c032,0x87e2002e,0x840540c2,0x87e9805c,0x87e9805c,0x87e38024,0x87b24079,0x87f4c026,0x87fe80b8,0x87d6c091,0x840540c2,0x84114032,0x87d7809e,0x8409c071,0x87df00f8,0x87f34004,0x84024003,0x87eb0042,0x87ea404d,0x87f70037,0x87f34004,0x840fc059,0x87f9407c,0x87f88090,0x87f70037,0x87eec07b,0x840540c2,0x87fa008e,0x87e68018,0x87fac08b,0x84060030,0x8406c035,0x87fe80b8,0x840a8083,};
const uint32_t FRONT_100_50_Y_transformed[262]={0xA40300E3,0xa40480c1,0xa40240ec,0xa403c0e6,0xa403c0e6,0xa40300e3,0xa40480c1,0xa40240ec,0xa40300e3,0xa40300e3,0xa40300e3,0xa403c0e6,0xa403c0e6,0xa40480c1,0xa40240ec,0xa40480c1,0xa403c0e6,0xa40240ec,0xa403c0e6,0xa403c0e6,0xa40300e3,0xa403c0e6,0xa40480c1,0xa40300e3,0xa403c0e6,0xa403c0e6,0xa40240ec,0xa405402d,0xa40300e3,0xa40480c1,0xa40480c1,0xa40240ec,0xa40480c1,0xa403c0e6,0xa40300e3,0xa40480c1,0xa40300e3,0xa40300e3,0xa40480c1,0xa40300e3,0xa40480c1,0xa40300e3,0xa40300e3,0xa403c0e6,0xa40240ec,0xa40480c1,0xa403c0e6,0xa40240ec,0xa40480c1,0xa403c0e6,0xa40180fd,0xa40480c1,0xa40300e3,0xa40300e3,0xa40480c1,0xa40300e3,0xa403c0e6,0xa40300e3,0xa403c0e6,0xa403c0e6,0xa403c0e6,0xa40300e3,0xa40240ec,0xa40480c1,0xa40300e3,0xa40240ec,0xa7fe8057,0xa7ec808f,0xa7b80008,0xa40240ec,0xa7e18036,0xa7ebc0a8,0xa42240a6,0xa4260095,0xa7d6409d,0xa7a8c028,0xa44b4014,0xa7838015,0xa7ab0039,0xa426c090,0xa7b28093,0xa78c4054,0xa4138025,0xa7b58052,0xa7abc03c,0xa78e80ac,0xa74c0021,0xa40b4080,0xa496c0f8,0xa7434083,0xa4180057,0xa45380b1,0xa7bb40fa,0xa7c5004a,0xa76580e4,0xa6600035,0xa74b8003,0xa7a50094,0xa7434083,0xa7894068,0xa42fc0fc,0xa777803c,0xa741c09d,0xa4cec0cc,0xa6bb80f1,0xa7b58052,0xa750c051,0xa76040dd,0xa41440e1,0xa6f2c0ef,0xa6d8803b,0xa7c400a3,0xa7f340eb,0xa7fa0061,0xa4404085,0xa6fd00ae,0xa721c043,0xa7db8021,0xa7ab0039,0xa41440e1,0xa6ef0076,0xa79600ef,0xa79cc092,0xa6db802f,0xa782c01a,0xa6e0c037,0xa78f4040,0xa7bd80d7,0xa7b0008d,0xa6f4c0c7,0xa41ac0af,0xa7b0008d,0xa79180cd,0xa729c0c6,0xa46e8067,0xa4194058,0xa4514049,0xa7d940d9,0xa747c0b5,0xa4d6408f,0xa742806f,0xa79300d3,0xa721c043,0xa7b1c061,0xa46340db,0xa6760038,0xa7e60014,0xa6428061,0xa79b40b0,0xa799c0ae,0xa73b001b,0xa46040cf,0xa79300d3,0xa7c14079,0xa7548062,0xa41b80a0,0xa7ddc0ef,0xa7a68063,0xa786402c,0xa73ec022,0xa7400071,0xa7f7c0dd,0xa744c0a1,0xa7ec808f,0xa7b0406b,0xa79480f1,0xa7b28093,0xa7b10064,0xa76580e4,0xa7f94093,0xa76f4099,0xa79b40b0,0xa796c0ea,0xa7574073,0xa7748028,0xa7da002b,0xa76a0043,0xa782c01a,0xa79300d3,0xa76ac046,0xa7c8c0f6,0xa796c0ea,0xa7d00053,0xa793c0d6,0xa7c2008b,0xa7cbc0e2,0xa7eec094,0xa7e980b3,0xa7cd4029,0xa7d2804d,0xa7bfc0cc,0xa41ac0af,0xa78dc05e,0xa7d00053,0xa7b9c0e4,0xa7f94093,0xa7f100f0,0xa7bf00c9,0xa40a806c,0xa7e24027,0xa412002f,0xa7db8021,0xa7cec0de,0xa7de801d,0xa7e3c02d,0xa40f00b3,0xa7ef809b,0xa7df40f1,0xa406c0da,0xa7e8c0bc,0xa40d80ad,0xa7e30028,0xa7d940d9,0xa403c0e6,0xa7cd4029,0xa4108031,0xa7d6409d,0xa7e980b3,0xa4084094,0xa7e6c011,0xa41140dd,0xa7dd00ea,0xa7f28007,0xa7fe8057,0xa7e6c011,0xa4168019,0xa7bd80d7,0xa403c0e6,0xa40780d5,0xa7ff40bb,0xa40480c1,0xa7ddc0ef,0xa40000f7,0xa4084094,0xa7f7c0dd,0xa4108031,0xa7fac064,0xa7eb00ad,0xa409009b,0xa7f700d8,0xa7fc40af,0xa7fa0061,0xa40240ec,0xa7fb806b,0xa4138025,0xa7f00019,0xa40cc0a2,0xa7f00019,0xa7f100f0,0xa41140dd,0xa7f28007,0xa403c0e6,0xa40cc0a2,0xa405402d,0xa7f700d8,0xa415c0eb,0xa7f7c0dd,0xa406c0da,0xa42300a9,0xa400c0f2,0xa420c0b8,0xa7fe8057,};

uint32_t *acceleration_X_ptr=FRONT_100_50_X_transformed;
uint32_t*acceleration_Y_ptr=FRONT_100_50_Y_transformed;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI3_Init(void);
static void MX_DMA_Init(void);
/* USER CODE BEGIN PFP */
void SPI_DMA_Restart(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{ 
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
ctr++;    
    if(ctr0==200)
		{
	      ctr0=0;
		  ctr2=0;
		}
    //if(ctr>3){
   // switch(memcmp(SPI_RX,RXCMD1,4))
      switch(ctr%2)
    { 
      case 0: 
       SPI_resp[0]=(*(acceleration_X_ptr+ctr0))>>24;
       SPI_resp[1]=(*(acceleration_X_ptr+ctr0))>>16;
       SPI_resp[2]=(*(acceleration_X_ptr+ctr0))>>8;
       SPI_resp[3]=(*(acceleration_X_ptr+ctr0));
       ctr0+=1;
       break;
      case 1:
       SPI_resp[0]=(*(acceleration_Y_ptr+ctr2))>>24;
       SPI_resp[1]=(*(acceleration_Y_ptr+ctr2))>>16;
       SPI_resp[2]=(*(acceleration_Y_ptr+ctr2))>>8;
       SPI_resp[3]=(*(acceleration_Y_ptr+ctr2));     
       ctr2+=1;
       break;
      
    }
   //}   
    
   /* HAL_DMA_DeInit(&hdma_spi3_tx);
    HAL_SPI_DeInit(&hspi3);
    //HAL_DMA_Init(&hdma_spi3_tx);
    HAL_SPI_Init(&hspi3);*/
    __HAL_RCC_SPI3_FORCE_RESET();
    __NOP();
    __HAL_RCC_SPI3_RELEASE_RESET();
    SPI_DMA_Restart();
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI3_Init();
  
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
     
     //if(ctr<530)
      HAL_SPI_TransmitReceive_DMA(&hspi3,SPI_resp,SPI_RX,4);
     // else
     __nop();
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI3|RCC_PERIPHCLK_FDCAN;
  PeriphClkInitStruct.PLL2.PLL2M = 40;
  PeriphClkInitStruct.PLL2.PLL2N = 125;
  PeriphClkInitStruct.PLL2.PLL2P = 1;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_0;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL2;
  PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief FDCAN1 Initialization Function
  * @param None
  * @retval None
  */


/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_SLAVE;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 0x0;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi3.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi3.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi3.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi3.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi3.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi3.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi3.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi3.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi3.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */
  
  /* USER CODE END SPI3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void SPI3_Init(void) {
    // Включение тактирования для SPI1 и GPIOA
    RCC->APB1LENR |= RCC_APB1LENR_SPI3EN;         // Включение тактирования SPI3
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;       // Включение тактирования GPIOC

    // Настройка GPIO для SPI1 (PA5: SCK, PA6: MISO, PA7: MOSI)
    GPIOC->MODER |= (0b10 << (10 * 2)) | (0b10 << (11 * 2)) | (0b10 << (12 * 2)); // Альтернативный режим
    GPIOC->AFR[1] |= (0x6 << ((10 - 8) * 4)) | (0x6 << ((11 - 8) * 4)) | (0x6 << ((12 - 8) * 4)); // AF6 для SPI3
    // Настройка параметров SPI1
   

    SPI3->CFG2 |= SPI_CFG2_SSM;    // Включение внутреннего подтягивающего резистора
    SPI3->CR1 |= SPI_CR1_SPE;                   // Включение SPI
    SPI3->CFG1|=SPI_CFG1_TXDMAEN|SPI_CFG1_RXDMAEN;
}

// Функция для инициализации DMA
void DMA_Init(void) 
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;        // Включить тактирование DMA2

    // Настройка канала DMA для передачи
    DMA1_Stream0->CR = 0; // Сброс всех настроек
    DMA1_Stream0->PAR = (uint32_t)&(SPI3->TXDR); // Адрес регистра данных SPI1
    DMA1_Stream0->M0AR = (uint32_t)SPI_resp;    // Адрес памяти
    DMA1_Stream0->NDTR = 4;      // Количество данных для передачи
    DMA1_Stream0->CR |= DMA_SxCR_MINC;          // Увеличение адреса памяти
    DMA1_Stream0->CR |= DMA_SxCR_DIR_0;         // Направление: память -> периферия
    DMA1_Stream0->CR |= DMA_SxCR_EN;            // Включить поток DMA
   // hdma_spi3_tx.XferCpltCallback=SPI_DMATransmitReceiveCplt;
    
    DMA1_Stream1->CR = 0;                       // Сброс всех настроек
    DMA1_Stream1->PAR = (uint32_t)&(SPI3->RXDR);  // Адрес регистра данных SPI3
    DMA1_Stream1->M0AR = (uint32_t)SPI_RX;    // Адрес памяти
    DMA1_Stream1->NDTR = 4 ;                     // Количество данных для приема
    DMA1_Stream1->CR |= DMA_SxCR_MINC;          // Увеличение адреса памяти
    DMA1_Stream1->CR |= DMA_SxCR_DIR_1;         // Направление: периферия -> память
    DMA1_Stream1->CR |= DMA_SxCR_EN;            // Включить поток DMA*/
}


void SPI_DMA_Restart(void) {
    // Деинициализация SPI
    SPI3->CR1 &= ~SPI_CR1_SPE;  // Отключить SPI

    // Остановка DMA
    DMA1_Stream0->CR &= ~DMA_SxCR_EN; // Остановить прием
   // Переинициализация DMA
    DMA_Init();
    // Переинициализация SPI
    SPI3_Init();

;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
