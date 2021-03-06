/**
 *!
 * \file        b_hal_uart.c
 * \version     v0.0.1
 * \date        2020/03/25
 * \author      Bean(notrynohigh@outlook.com)
 *******************************************************************************
 * @attention
 * 
 * Copyright (c) 2020 Bean
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SUARTL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************
 */
   
/*Includes ----------------------------------------------*/
#include "b_hal.h" 
#include "b_utils.h"
#include <string.h>
#include <stdio.h>
/** 
 * \addtogroup B_HAL
 * \{
 */

/** 
 * \addtogroup UART
 * \{
 */

/** 
 * \defgroup UART_Private_TypesDefinitions
 * \{
 */
   
/**
 * \}
 */
   
/** 
 * \defgroup UART_Private_Defines
 * \{
 */
bSECTION_DEF_RAM(b_hal_uart, bHalUartRxInfo_t);  
/**
 * \}
 */
   
/** 
 * \defgroup UART_Private_Macros
 * \{
 */
   
/**
 * \}
 */
   
/** 
 * \defgroup UART_Private_Variables
 * \{
 */

/**
 * \}
 */
   
/** 
 * \defgroup UART_Private_FunctionPrototypes
 * \{
 */
   
/**
 * \}
 */
   
/** 
 * \defgroup UART_Private_Functions
 * \{
 */
/**
 * \brief Determine idle events. Called in bExec()
 */
static void _bHalUartDetectIdle()
{
    uint32_t c_tick = bUtilGetTick();
    
    bSECTION_FOR_EACH(b_hal_uart, bHalUartRxInfo_t, ptmp)
    {
        if(ptmp->index > 0)
        {
            if(ptmp->l_index == 0)
            {
                ptmp->l_index = ptmp->index;
                ptmp->l_tick = bUtilGetTick();
            }
            else
            {
                if(ptmp->index != ptmp->l_index)
                {
                    ptmp->l_index = ptmp->index;
                    ptmp->l_tick = bUtilGetTick();
                }
                else if(bUtilGetTick() - ptmp->l_tick > ptmp->idle_threshold)
                {
                    if(ptmp->handler != NULL)
                    {
                        ptmp->handler(ptmp->pbuf, ptmp->index);
                        ptmp->index = 0;
                    }
                }
            }
        }
    }
}

BOS_REG_POLLING_FUNC(_bHalUartDetectIdle);

/**
 * \}
 */
   
/** 
 * \addtogroup UART_Exported_Functions
 * \{
 */

void bHalUartSend(bHalUartNumber_t uart, uint8_t *pbuf, uint16_t len)
{
    switch(uart)
    {
        case B_HAL_UART_1:
            printf("%s", pbuf);
            break;
        case B_HAL_UART_2:
    
            break;        
        default:
            break;
    }
}




/**
 * \brief This function handles Uart rx 1Byte interrupts.
 * \param no Uart number \ref bHalUartNumber_t
 * \param dat The received data
 */ 
void bHalUartRxIRQ_Handler(bHalUartNumber_t uart, uint8_t dat)
{
    if(uart >= B_HAL_UART_NUMBER)
    {
        return;
    }
    bSECTION_FOR_EACH(b_hal_uart, bHalUartRxInfo_t, ptmp)
    {
        if(ptmp->uart == uart)
        {
            if(ptmp->index < ptmp->buf_len)
            {
                ptmp->pbuf[ptmp->index++] = dat;
            }
            break;
        }
    }
}




/**
 * \}
 */

/**
 * \}
 */


/**
 * \}
 */

/************************ Copyright (c) 2020 Bean *****END OF FILE****/


