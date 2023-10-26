#include "stm32_HC05.h"
#include <string.h>

#define HC05_COMMAND_MODE_TIMEOUT 1000  // Timeout for entering/exiting command mode in milliseconds
#define HC05_RESPONSE_TIMEOUT     1000  // Timeout for receiving response in milliseconds

void HC05_Init(HC05_HandleTypeDef *hc05)
{
  hc05->huart = &HC05_UART;
  hc05->initialized = false;
}

HC05_StatusTypeDef HC05_SendCommand(HC05_HandleTypeDef *hc05, const char *command)
{
  HAL_UART_Transmit(hc05->huart, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);

  return HC05_OK;
}

HC05_StatusTypeDef HC05_ReceiveResponse(HC05_HandleTypeDef *hc05, char *response, uint32_t timeout)
{
  uint8_t rxByte;
  uint32_t tickStart = HAL_GetTick();
  uint32_t index = 0;

  memset(response, 0, strlen(response));

  while (true)
  {
    if (HAL_UART_Receive(hc05->huart, &rxByte, 1, 0) == HAL_OK)
    {
      response[index++] = rxByte;

      if (strstr(response, "OK") != NULL)
      {
        return HC05_OK;
      }
      else if (strstr(response, "ERROR") != NULL)
      {
        return HC05_ERROR;
      }
    }

    if ((timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickStart) >= timeout))
    {
      return HC05_TIMEOUT;
    }
  }
}

bool HC05_CheckOKResponse(const char *response)
{
  if (strstr(response, "OK") != NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

HC05_StatusTypeDef HC05_SetBaudRate(HC05_HandleTypeDef *hc05, uint32_t baudRate)
{
  char command[30];
  sprintf(command, "AT+UART=%lu,1,0\r\n", baudRate);

  HC05_SendCommand(hc05, "AT");
  HC05_ReceiveResponse(hc05, command, HC05_RESPONSE_TIMEOUT);

  if (HC05_CheckOKResponse(command))
  {
    return HC05_OK;
  }
  else
  {
    return HC05_ERROR;
  }
}

HC05_StatusTypeDef HC05_SetDeviceName(HC05_HandleTypeDef *hc05, const char *name)
{
  char command[30];
  sprintf(command, "AT+NAME=%s\r\n", name);

  HC05_SendCommand(hc05, command);
  HC05_ReceiveResponse(hc05, command, HC05_RESPONSE_TIMEOUT);

  if (HC05_CheckOKResponse(command))
  {
    return HC05_OK;
  }
  else
  {
    return HC05_ERROR;
  }
}

HC05_StatusTypeDef HC05_SetDevicePin(HC05_HandleTypeDef *hc05, const char *pin)
{
  char command[30];
  sprintf(command, "AT+PIN=%s\r\n", pin);

  HC05_SendCommand(hc05, command);
  HC05_ReceiveResponse(hc05, command, HC05_RESPONSE_TIMEOUT);

  if (HC05_CheckOKResponse(command))
  {
    return HC05_OK;
  }
  else
  {
    return HC05_ERROR;
  }
}

HC05_StatusTypeDef HC05_EnterCommandMode(HC05_HandleTypeDef *hc05)
{
  HC05_SendCommand(hc05, "+++");
  HAL_Delay(1000); // Wait for command mode responseHC05_StatusTypeDef HC05_ExitCommandMode(HC05_HandleTypeDef *hc05)
{
  HC05_SendCommand(hc05, "AT");
  HC05_ReceiveResponse(hc05, "AT", HC05_RESPONSE_TIMEOUT);

  if (HC05_CheckOKResponse("AT"))
  {
    return HC05_OK;
  }
  else
  {
    return HC05_ERROR;
  }
}

HC05_StatusTypeDef HC05_Reset(HC05_HandleTypeDef *hc05)
{
  HC05_SendCommand(hc05, "AT+RESET");
  HC05_ReceiveResponse(hc05, "AT+RESET", HC05_RESPONSE_TIMEOUT);

  if (HC05_CheckOKResponse("AT+RESET"))
  {
    return HC05_OK;
  }
  else
  {
    return HC05_ERROR;
  }
}