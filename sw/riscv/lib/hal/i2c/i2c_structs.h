/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : i2c_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   i2c_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _I2C_STRUCTS_H
#define I2C_STRUCTS

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

typedef enum RXILVL_enum {
  rxlvl1         =  0,                         /*!< 1 character                                                                                         */
  rxlvl4         =  1,                         /*!< 4 characters                                                                                        */
  rxlvl8         =  2,                         /*!< 8 characters                                                                                        */
  rxlvl16        =  3,                         /*!< 16 characters                                                                                       */
  rxlvl30        =  4,                         /*!< 30 characters                                                                                       */
} RXILVL_t;

typedef enum FMTILVL_enum {
  fmtlvl1        =  0,                         /*!< 1 character                                                                                         */
  fmtlvl4        =  1,                         /*!< 4 characters                                                                                        */
  fmtlvl8        =  2,                         /*!< 8 characters                                                                                        */
  fmtlvl16       =  3,                         /*!< 16 characters                                                                                       */
} FMTILVL_t;



typedef struct {
  union
  {
    struct 
    {
      uint8_t        ENABLEHOST          :1;   /*!< bit: 0    Enable Host I2C functionality                                                                       */
      uint8_t        ENABLETARGET        :1;   /*!< bit: 1    Enable Target I2C functionality                                                                     */
      uint32_t       _reserved           :30;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CTRL;

  union
  {
    struct 
    {
      uint8_t        FMTFULL             :1;   /*!< bit: 0    FMT buffer is full                                                                                  */
      uint8_t        RXFULL              :1;   /*!< bit: 1    RX buffer is full                                                                                   */
      uint8_t        FMTEMPTY            :1;   /*!< bit: 2    FMT FIFO is empty                                                                                   */
      uint8_t        RXEMPTY             :1;   /*!< bit: 5    RX FIFO is empty                                                                                    */
      uint8_t        HOSTIDLE            :1;   /*!< bit: 3    Host functionality is idle. No Host transaction is in progress                                      */
      uint8_t        TARGETIDLE          :1;   /*!< bit: 4    Target functionality is idle. No Target transaction is in progress                                  */
      uint8_t        TXFULL              :1;   /*!< bit: 6    TX FIFO is full                                                                                     */
      uint8_t        ACQFULL             :1;   /*!< bit: 7    ACQ FIFO is full                                                                                    */
      uint8_t        TXEMPTY             :1;   /*!< bit: 8    TX FIFO is empty                                                                                    */
      uint8_t        ACQEMPTY            :1;   /*!< bit: 9    ACQ FIFO is empty                                                                                   */
      uint32_t       _reserved           :22;  
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
      uint8_t        FBYTE               :8;   /*!< bit: 7:0  Format Byte. Directly transmitted if no flags are set.                                              */
      uint8_t        START               :1;   /*!< bit: 8    Issue a START condition before transmitting BYTE.                                                   */
      uint8_t        STOP                :1;   /*!< bit: 9    Issue a STOP condition after this operation                                                         */
      uint8_t        READ                :1;   /*!< bit: 10   Read BYTE bytes from I2C. (256 if BYTE==0)                                                          */
      uint8_t        RCONT               :1;   /*!< bit: 11   Do not NAK the last byte read, let the read operation continue                                      */
      uint8_t        NAKOK               :1;   /*!< bit: 12   Do not signal an exception if the current byte is not ACK'd                                         */
      uint32_t       _reserved           :19;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } FDATA;

  union
  {
    struct 
    {
      uint8_t        RXRST               :1;   /*!< bit: 0    RX fifo reset. Write 1 to the register resets RX_FIFO. Read returns 0                               */
      uint8_t        FMTRST              :1;   /*!< bit: 1    FMT fifo reset. Write 1 to the register resets FMT_FIFO. Read returns 0                             */
      RXILVL_t       RXILVL              :3;   /*!< bit: 4:2  Trigger level for RX interrupts. If the FIFO depth exceeds this setting, it raises rx_watermark interrupt.*/
      FMTILVL_t      FMTILVL             :2;   /*!< bit: 6:5  Trigger level for FMT interrupts. If the FIFO depth falls below this setting, it raises fmt_watermark interrupt.*/
      uint8_t        ACQRST              :1;   /*!< bit: 7    ACQ FIFO reset. Write 1 to the register resets it. Read returns 0                                   */
      uint8_t        TXRST               :1;   /*!< bit: 8    TX FIFO reset. Write 1 to the register resets it. Read returns 0                                    */
      uint32_t       _reserved           :23;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } FIFO_CTRL;

  union
  {
    struct 
    {
      uint8_t        FMTLVL              :6;   /*!< bit: 5:0  Current fill level of FMT fifo                                                                      */
      uint8_t        RXLVL               :6;   /*!< bit: 21:16Current fill level of RX fifo                                                                       */
      uint8_t        TXLVL               :6;   /*!< bit: 13:8 Current fill level of TX fifo                                                                       */
      uint8_t        ACQLVL              :6;   /*!< bit: 29:24Current fill level of ACQ fifo                                                                      */
      uint8_t        _reserved           :8;   
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } FIFO_STATUS;

  union
  {
    struct 
    {
      uint8_t        TXOVRDEN            :1;   /*!< bit: 0    Override the SDA and SCL TX signals.                                                                */
      uint8_t        SCLVAL              :1;   /*!< bit: 1    Value for SCL Override. Set to 0 to drive TX Low, and set to 1 for high-Z                           */
      uint8_t        SDAVAL              :1;   /*!< bit: 2    Value for SDA Override. Set to 0 to drive TX Low, and set to 1 for high-Z                           */
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } OVRD;

  union
  {
    struct 
    {
      uint16_t       SCL_RX              :16;  /*!< bit: 15:0 Last 16 oversampled values of SCL. Most recent bit is bit 0, oldest 15.                             */
      uint16_t       SDA_RX              :16;  /*!< bit: 31:16Last 16 oversampled values of SDA. Most recent bit is bit 16, oldest 31.                            */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } VAL;

  union
  {
    struct 
    {
      uint16_t       THIGH               :16;  /*!< bit: 15:0 The actual time to hold SCL high in a given pulse                                                   */
      uint16_t       TLOW                :16;  /*!< bit: 31:16The actual time to hold SCL low between any two SCL pulses                                          */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMING0;

  union
  {
    struct 
    {
      uint16_t       T_R                 :16;  /*!< bit: 15:0 The nominal rise time to anticipate for the bus (depends on capacitance)                            */
      uint16_t       T_F                 :16;  /*!< bit: 31:16The nominal fall time to anticipate for the bus (influences SDA hold times)                         */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMING1;

  union
  {
    struct 
    {
      uint16_t       TSU_STA             :16;  /*!< bit: 15:0 Actual setup time for repeated start signals                                                        */
      uint16_t       THD_STA             :16;  /*!< bit: 31:16Actual hold time for start signals                                                                  */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMING2;

  union
  {
    struct 
    {
      uint16_t       TSU_DAT             :16;  /*!< bit: 15:0 Actual setup time for data (or ack) bits                                                            */
      uint16_t       THD_DAT             :16;  /*!< bit: 31:16Actual hold time for data (or ack) bits (Note, where required, the parameters TVD_DAT is taken to be THD_DAT+T_F)*/
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMING3;

  union
  {
    struct 
    {
      uint16_t       TSU_STO             :16;  /*!< bit: 15:0 Actual setup time for stop signals                                                                  */
      uint16_t       T_BUF               :16;  /*!< bit: 31:16Actual time between each STOP signal and the following START signal                                 */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMING4;

  union
  {
    struct 
    {
      uint32_t       VAL                 :31;  /*!< bit: 30:0 Clock stretching timeout value (in units of input clock frequency)                                  */
      uint8_t        EN                  :1;   /*!< bit: 31   Enable timeout feature                                                                              */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMEOUT_CTRL;

  union
  {
    struct 
    {
      uint8_t        ADDRESS0            :7;   /*!< bit: 6:0  I2C target address number 0                                                                         */
      uint8_t        MASK0               :7;   /*!< bit: 13:7 I2C target mask number 0                                                                            */
      uint8_t        ADDRESS1            :7;   /*!< bit: 20:14I2C target address number 1                                                                         */
      uint8_t        MASK1               :7;   /*!< bit: 27:21I2C target mask number 1                                                                            */
      uint8_t        _reserved           :4;   
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TARGET_ID;

  union
  {
    struct 
    {
      uint8_t        ABYTE               :8;   /*!< bit: 7:0  Address for accepted transaction or acquired byte                                                   */
      uint8_t        SIGNAL              :2;   /*!< bit: 9:8  Host issued a START before transmitting ABYTE, a STOP or a RESTART after the preceeding ABYTE       */
      uint32_t       _reserved           :22;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } ACQDATA;

  union
  {
    struct 
    {
      uint8_t        TXDATA              :8;   
      uint32_t       _reserved           :24;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TXDATA;

  union
  {
    struct 
    {
      uint8_t        ENABLEADDR          :1;   /*!< bit: 0    Enable clock stretching after address matching completes                                            */
      uint8_t        ENABLETX            :1;   /*!< bit: 1    Enable clock stretching after ongoing transmit (read) transaction completes                         */
      uint8_t        ENABLEACQ           :1;   /*!< bit: 2    Enable clock stretching after ongoing acquire (write) transaction completes                         */
      uint8_t        STOP                :1;   /*!< bit: 3    Stop clock stretching and resume normal operation                                                   */
      uint32_t       _reserved           :28;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } STRETCH_CTRL;

  union
  {
    struct 
    {
      uint32_t       HOST_TIMEOUT_CTRL   :32;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } HOST_TIMEOUT_CTRL;

} i2c;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _I2C_STRUCTS_C_SRC



#endif  /* _I2C_STRUCTS_C_SRC */

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



#endif /* _I2C_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
