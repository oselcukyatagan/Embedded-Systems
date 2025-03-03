
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdint.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

	uint8_t AHT10_Adress = 0x38;
	uint8_t triggerCommand = 0xac;
	uint8_t receiveByteSize = 8;
	uint8_t sensorData[6];
	uint8_t sensorDataSize = 6;
	uint32_t temp;


	char message[50];



	HAL_StatusTypeDef readTemp(uint8_t sensorAdress, uint8_t *dataToTransmit, uint8_t dataToTransmitSize, uint32_t *tempData,
			uint8_t *sensorDataArray, uint8_t sensorDataArraySize){


			HAL_StatusTypeDef result;


			result = HAL_I2C_Master_Transmit(&hi2c1, sensorAdress << 1, dataToTransmit, dataToTransmitSize, HAL_MAX_DELAY);
			if(result != HAL_OK) return result;
			HAL_Delay(75);

			result = HAL_I2C_Master_Receive(&hi2c1, (sensorAdress << 1) | 0x01, sensorDataArray, sensorDataArraySize, HAL_MAX_DELAY);
			if(result != HAL_OK) return result;

			*tempData = sensorDataArray[3] << 12 | sensorDataArray[4] << 4 | sensorDataArray[5] >> 4;

			return HAL_OK;

		}


	uint32_t power(uint16_t base, uint16_t exp) {
		    uint32_t res = 1;
		    for (uint16_t i = 0; i < exp; i++) {
		        res *= base;
		    }
		    return res;
		}

	float getTempInCelsius(uint32_t tempVal) {

		return ((float)tempVal / (power(2,20)) ) * 200.0 - 50.0;

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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if (readTemp(AHT10_Adress, &triggerCommand, 1, &temp, &sensorData, sensorDataSize) == HAL_OK){

		  float temperature = getTempInCelsius(temp);
		  sprintf(message, " raw value: %lu\r\n", temp);
		  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);

	  }

	  HAL_Delay(1000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
