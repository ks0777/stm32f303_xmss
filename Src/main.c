#include "main.h"

void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();

  SystemClock_Config();
  trigger_init();

  xmss_params params;
  xmss_parse_oid(&params, 0xd);

  unsigned char seed[params.n];
  unsigned char pub_seed[params.n];
  unsigned char pk1[params.wots_sig_bytes];
  unsigned char pk2[params.wots_sig_bytes];
  unsigned char sig[params.wots_sig_bytes];
  unsigned char m[params.n];
  uint32_t addr[8] = {0};
  
  memset(addr, '\0', 8 * sizeof(uint32_t));
  memset(seed, '\0', params.n);
  memset(pub_seed, '\0', params.n);
  memset(m, '\xff', params.n);
  m[0] = '\xef';
  
  wots_pkgen(&params, pk1, seed, pub_seed, addr);
  wots_sign(&params, sig, m, seed, pub_seed, addr);
  
  m[0] = '\xff'; // Set first messagechunk to biggest possible value
  unsigned char overwrite[] = "\xA9\xE6\x8B\xAE\x2A\xB5\x44\xA9\x64\x21\xBA\x15\x27\x82\xC2\x30\xE0\x93\x6C\x19\x36\xC8\x66\x8F";
  memcpy(sig, overwrite, 24); // Overwrite hash of first chain with the correct value for the forged message chunk
  unsigned char overwrite2[] = "\xEB\xB4\xC5\xD7\xF0\xFC\x5F\x10\xAD\x9C\xFB\xDD\x9F\x02\x49\xFB\x57\xF1\xE3\x5F\x66\x50\xE5\x44";
  memcpy(sig + params.wots_sig_bytes - params.n , overwrite2, 24); // Overwrite hash of checksum chain with the final value from the public key for the new checksum. This chain will be faulted such that no further hashes are performed.
  
  wots_pk_from_sig(&params, pk2, sig, m, pub_seed, addr);
  
  if (memcmp(pk1, pk2, params.wots_sig_bytes)) {
    HAL_Delay(500);
  }

  while (1)
  {
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
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
}
#endif /* USE_FULL_ASSERT */
