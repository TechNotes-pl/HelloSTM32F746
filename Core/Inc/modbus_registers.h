/*
 * modbus_registers.h
 *
 *  Created: 19 june 2020
 *      Author: Technotes-pl
 */

#include "stm32f7xx_hal.h"
#include "mb.h"
#include "mbport.h"

#ifndef INC_MODBUS_REGISTERS_H_
#define INC_MODBUS_REGISTERS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* -------------- Modbus registers configuration ------------------------*/

#define REG_INPUT_START 1000
#define REG_INPUT_NREGS 4

static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];



/**
  * Refresh Modbus registers values
  */
void ModbusRegsRefresh(void);

/**
  * @brief ModBus register input callback
  * @retval eMBErrorCode
  */
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );

/**
  * @brief ModBus register input callback
  * @retval eMBErrorCode
  */
eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );

/**
  * @brief ModBus register input callback
  * @retval eMBErrorCode
  */
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );

/**
  * @brief ModBus register input callback
  * @retval eMBErrorCode
  */
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );

#ifdef __cplusplus
}
#endif
#endif /* INC_MODBUS_REGISTERS_H_ */
