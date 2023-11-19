/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : uart_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   uart_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _UART_STRUCTS_H
#define UART_STRUCTS

/****************************************************************************/
/**                                                                        **/
/**                            MODULES USED                                **/
/**                                                                        **/
/****************************************************************************/

#include <inttypes.h>

/****************************************************************************/
/**                                                                        **/
/**                       DEFINITIONS AND MACROS                           **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                       TYPEDEFS AND STRUCTURES                          **/
/**                                                                        **/
/****************************************************************************/

typedef enum RXBLVL_enum {
  break2         =  0,                         /*!< 2 characters                                                                                        */
  break4         =  1,                         /*!< 4 characters                                                                                        */
  break8         =  2,                         /*!< 8 characters                                                                                        */
  break16        =  3,                         /*!< 16 characters                                                                                       */
} RXBLVL_t;

typedef enum RXILVL_enum {
  rxlvl1         =  0,                         /*!< 1 character                                                                                         */
  rxlvl4         =  1,                         /*!< 4 characters                                                                                        */
  rxlvl8         =  2,                         /*!< 8 characters                                                                                        */
  rxlvl16        =  3,                         /*!< 16 characters                                                                                       */
  rxlvl30        =  4,                         /*!< 30 characters                                                                                       */
} RXILVL_t;

typedef enum TXILVL_enum {
  txlvl1         =  0,                         /*!< 2 characters                                                                                        */
  txlvl4         =  1,                         /*!< 4 characters                                                                                        */
  txlvl8         =  2,                         /*!< 8 characters                                                                                        */
  txlvl16        =  3,                         /*!< 16 characters                                                                                       */
} TXILVL_t;



typedef struct {
  union
  {
    struct 
    {
      uint8_t        TX                  :1;   /*!< bit: 0    TX enable                                                                                           */
      uint8_t        RX                  :1;   /*!< bit: 1    RX enable                                                                                           */
      uint8_t        NF                  :1;   /*!< bit: 2    RX noise filter enable. If the noise filter is enabled, RX line goes through the 3-tap repetition code. It ignores single IP clock period noise.*/
      uint8_t        SLPBK               :1;   /*!< bit: 4    System loopback enable.  If this bit is turned on, any outgoing bits to TX are received through RX. See Block Diagram. Note that the TX line goes 1 if System loopback is enabled.*/
      uint8_t        LLPBK               :1;   /*!< bit: 5    Line loopback enable.  If this bit is turned on, incoming bits are forwarded to TX for testing purpose. See Block Diagram. Note that the internal design sees RX value as 1 always if line loopback is enabled.*/
      uint8_t        PARITY_EN           :1;   /*!< bit: 6    If true, parity is enabled in both RX and TX directions.                                            */
      uint8_t        PARITY_ODD          :1;   /*!< bit: 7    If PARITY_EN is true, this determines the type, 1 for odd parity, 0 for even.                       */
      RXBLVL_t       RXBLVL              :2;   /*!< bit: 9:8  Trigger level for RX break detection. Sets the number of character times the line must be low to detect a break.*/
      uint16_t       NCO                 :16;  /*!< bit: 31:16BAUD clock rate control.                                                                            */
      uint8_t        _reserved           :7;   
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CTRL;

  union
  {
    struct 
    {
      uint8_t        TXFULL              :1;   /*!< bit: 0    TX buffer is full                                                                                   */
      uint8_t        RXFULL              :1;   /*!< bit: 1    RX buffer is full                                                                                   */
      uint8_t        TXEMPTY             :1;   /*!< bit: 2    TX FIFO is empty                                                                                    */
      uint8_t        TXIDLE              :1;   /*!< bit: 3    TX FIFO is empty and all bits have been transmitted                                                 */
      uint8_t        RXIDLE              :1;   /*!< bit: 4    RX is idle                                                                                          */
      uint8_t        RXEMPTY             :1;   /*!< bit: 5    RX FIFO is empty                                                                                    */
      uint32_t       _reserved           :26;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } STATUS;

  union
  {
    struct 
    {
      uint8_t        RDATA               :8;   
      uint32_t       _reserved           :24;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RDATA;

  union
  {
    struct 
    {
      uint8_t        WDATA               :8;   
      uint32_t       _reserved           :24;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } WDATA;

  union
  {
    struct 
    {
      uint8_t        RXRST               :1;   /*!< bit: 0    RX fifo reset. Write 1 to the register resets RX_FIFO. Read returns 0                               */
      uint8_t        TXRST               :1;   /*!< bit: 1    TX fifo reset. Write 1 to the register resets TX_FIFO. Read returns 0                               */
      RXILVL_t       RXILVL              :3;   /*!< bit: 4:2  Trigger level for RX interrupts. If the FIFO depth is greater than or equal to the setting, it raises rx_watermark interrupt.*/
      TXILVL_t       TXILVL              :2;   /*!< bit: 6:5  Trigger level for TX interrupts. If the FIFO depth is less than the setting, it raises tx_watermark interrupt.*/
      uint32_t       _reserved           :25;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } FIFO_CTRL;

  union
  {
    struct 
    {
      uint8_t        TXLVL               :6;   /*!< bit: 5:0  Current fill level of TX fifo                                                                       */
      uint8_t        RXLVL               :6;   /*!< bit: 21:16Current fill level of RX fifo                                                                       */
      uint32_t       _reserved           :20;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } FIFO_STATUS;

  union
  {
    struct 
    {
      uint8_t        TXEN                :1;   /*!< bit: 0    Enable TX pin override control                                                                      */
      uint8_t        TXVAL               :1;   /*!< bit: 1    Write to set the value of the TX pin                                                                */
      uint32_t       _reserved           :30;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } OVRD;

  union
  {
    struct 
    {
      uint16_t       RX                  :16;  /*!< bit: 15:0 Last 16 oversampled values of RX. Most recent bit is bit 0, oldest 15.                              */
      uint16_t       _reserved           :16;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } VAL;

  union
  {
    struct 
    {
      uint32_t       VAL                 :24;  /*!< bit: 23:0 RX timeout value in UART bit times                                                                  */
      uint8_t        EN                  :1;   /*!< bit: 31   Enable RX timeout feature                                                                           */
      uint8_t        _reserved           :7;   
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMEOUT_CTRL;

} uart;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _UART_STRUCTS_C_SRC



#endif  /* _UART_STRUCTS_C_SRC */

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED FUNCTIONS                            **/
/**                                                                        **/
/****************************************************************************/


/****************************************************************************/
/**                                                                        **/
/**                          INLINE FUNCTIONS                              **/
/**                                                                        **/
/****************************************************************************/



#endif /* _UART_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
