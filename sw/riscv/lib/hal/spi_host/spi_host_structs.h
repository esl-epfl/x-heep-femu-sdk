/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : spi_host_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   spi_host_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _SPI_HOST_STRUCTS_H
#define SPI_HOST_STRUCTS

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



typedef struct {
  union
  {
    struct 
    {
      uint8_t        SPIEN               :1;   /*!< bit: 31   Enables the SPI host.  On reset, this field is 0, meaning    that no transactions can proceed.      */
      uint8_t        SW_RST              :1;   /*!< bit: 30   Clears the entire IP to the reset state when set to 1, including    the FIFOs, the CDC's, the core state machine and the shift register.    In the current implementation, the CDC FIFOs are drained not reset.    Therefore software must confirm that both FIFO's empty before releasing    the IP from reset.*/
      uint8_t        OUTPUT_EN           :1;   /*!< bit: 29   Enable the SPI host output buffers for the sck, csb, and sd lines.  This allows    the SPI_HOST IP to connect to the same bus as other SPI controllers without    interference.*/
      uint8_t        TX_WATERMARK        :8;   /*!< bit: 15:8 If !!EVENT_ENABLE.TXWM is set, the IP will send    an interrupt when the depth of the TX FIFO drops below    TX_WATERMARK words (32b each).*/
      uint8_t        RX_WATERMARK        :8;   /*!< bit: 7:0  If !!EVENT_ENABLE.RXWM is set, the IP will send    an interrupt when the depth of the RX FIFO reaches    RX_WATERMARK words (32b each).*/
      uint16_t       _reserved           :13;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CONTROL;

  union
  {
    struct 
    {
      uint8_t        READY               :1;   /*!< bit: 31   When high, indicates the SPI host is ready to receive    commands. Writing to COMMAND when READY is low is    an error, and will trigger an interrupt.    */
      uint8_t        ACTIVE              :1;   /*!< bit: 30   When high, indicates the SPI host is processing a previously    issued command.                     */
      uint8_t        TXFULL              :1;   /*!< bit: 29   When high, indicates that the transmit data fifo is full.    Any further writes to !!RXDATA will create an error interrupt.*/
      uint8_t        TXEMPTY             :1;   /*!< bit: 28   When high, indicates that the transmit data fifo is empty.                                          */
      uint8_t        TXSTALL             :1;   /*!< bit: 27   If high, signifies that an ongoing transaction has stalled    due to lack of data in the TX FIFO    */
      uint8_t        TXWM                :1;   /*!< bit: 26   If high, the amount of data in the TX FIFO has fallen below the    level of !!CONTROL.TX_WATERMARK words (32b each).*/
      uint8_t        RXFULL              :1;   /*!< bit: 25   When high, indicates that the receive fifo is full.  Any    ongoing transactions will stall until firmware reads some    data from !!RXDATA.*/
      uint8_t        RXEMPTY             :1;   /*!< bit: 24   When high, indicates that the receive fifo is empty.    Any reads from RX FIFO will cause an error interrupt.    */
      uint8_t        RXSTALL             :1;   /*!< bit: 23   If high, signifies that an ongoing transaction has stalled    due to lack of available space in the RX FIFO*/
      uint8_t        BYTEORDER           :1;   /*!< bit: 22   The value of the ByteOrder parameter, provided so that firmware    can confirm proper IP configuration.*/
      uint8_t        RXWM                :1;   /*!< bit: 20   If high, the number of 32-bits in the RX FIFO now exceeds the    !!CONTROL.RX_WATERMARK entries (32b each).*/
      uint8_t        CMDQD               :4;   /*!< bit: 19:16Command queue depth. Indicates how many unread 32-bit words are    currently in the command segment queue.*/
      uint8_t        RXQD                :8;   /*!< bit: 15:8 Receive queue depth. Indicates how many unread 32-bit words are    currently in the RX FIFO.  When active, this result may an    underestimate due to synchronization delays.*/
      uint8_t        TXQD                :8;   /*!< bit: 7:0  Transmit queue depth. Indicates how many unsent 32-bit words    are currently in the TX FIFO.  When active, this result may    be an overestimate due to synchronization delays,*/
      uint8_t        _reserved           :1;   
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } STATUS;

  union
  {
    struct 
    {
      uint8_t        CPOL                :1;   /*!< bit: 31   The polarity of the sck clock signal.  When CPOL is 0,    sck is low when idle, and emits high pulses.   When CPOL    is low, sck is high when idle, and emits a series of low    pulses.    */
      uint8_t        CPHA                :1;   /*!< bit: 30   The phase of the sck clock signal relative to the data. When    CPHA = 0, the data changes on the trailing edge of sck    and is typically sampled on the leading edge.  Conversely    if CPHA = 1 high, data lines change on the leading edge of    sck and are typically sampled on the trailing edge.    CPHA should be chosen to match the phase of the selected    device.  The sampling behavior is modified by the    !!CONFIGOPTS.FULLCYC bit.    */
      uint8_t        FULLCYC             :1;   /*!< bit: 29   Full cycle.  Modifies the CPHA sampling behaviour to allow    for longer device logic setup times.  Rather than sampling the SD    bus a half cycle after shifting out data, the data is sampled    a full cycle after shifting data out.  This means that if    CPHA = 0, data is shifted out on the trailing edge, and    sampled a full cycle later.  If CPHA = 1, data is shifted and    sampled with the trailing edge, also separated by a    full cycle.*/
      uint8_t        CSNLEAD             :4;   /*!< bit: 27:24CS_N Leading Time.  Indicates the number of half sck cycles,    CSNLEAD+1, to leave between the falling edge of cs_n and    the first edge of sck.  Setting this register to zero    corresponds to the minimum delay of one-half sck cycle*/
      uint8_t        CSNTRAIL            :4;   /*!< bit: 23:20CS_N Trailing Time.  Indicates the number of half sck cycles,    CSNTRAIL+1, to leave between last edge of sck and the rising    edge of cs_n. Setting this register to zero corresponds    to the minimum delay of one-half sck cycle.*/
      uint8_t        CSNIDLE             :4;   /*!< bit: 19:16Minimum idle time between commands. Indicates the minimum    number of sck half-cycles to hold cs_n high between commands.    Setting this register to zero creates a minimally-wide CS_N-high    pulse of one-half sck cycle.*/
      uint16_t       CLKDIV              :16;  /*!< bit: 15:0 Core clock divider.  Slows down subsequent SPI transactions by a    factor of (CLKDIV+1) relative to the core clock frequency.  The    period of sck, T(sck) then becomes `2*(CLK_DIV+1)*T(core)`*/
      uint8_t        _reserved           :1;   
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CONFIGOPTS;

  union
  {
    struct 
    {
      uint32_t       CSID                :32;  /*!< bit: 31:0 Chip Select ID                                                                                      */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CSID;

  union
  {
    struct 
    {
      uint8_t        DIRECTION           :2;   /*!< bit: 28:27The direction for the following command: "0" = Dummy cycles    (no TX/RX). "1" = Rx only, "2" = Tx only, "3" = Bidirectional    Tx/Rx (Standard SPI mode only).*/
      uint8_t        SPEED               :2;   /*!< bit: 26:25The speed for this command segment: "0" = Standard SPI. "1" = Dual SPI.    "2"=Quad SPI,  "3": RESERVED.*/
      uint8_t        CSAAT               :1;   /*!< bit: 24   Chip select active after transaction.  If CSAAT = 0, the    chip select line is raised immediately at the end of the    command segment.   If !!COMMAND.CSAAT = 1, the chip select    line is left low at the end of the current transaction    segment.  This allows the creation longer, more    complete SPI transactions, consisting of several separate    segments for issuing instructions, pausing for dummy cycles,    and transmitting or receiving data from the device.*/
      uint32_t       LEN                 :24;  /*!< bit: 23:0 Segment Length.     For read or write segments, this field controls the    number of 1-byte bursts to transmit and or receive in    this command segment.  The number of cyles required    to send or received a byte will depend on !!COMMAND.SPEED.    For dummy segments, (!!COMMAND.DIRECTION == 0), this register    controls the number of dummy cycles to issue.    The number of bytes (or dummy cycles) in the segment will be    equal to !!COMMAND.LEN + 1.    */
      uint8_t        _reserved           :3;   
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } COMMAND;

  union
  {
    struct 
    {
      uint8_t        CSIDINVAL           :1;   /*!< bit: 4    Invalid CSID: If this bit is set, the block sends an error interrupt whenever    a command is submitted, but CSID exceeds NumCS.*/
      uint8_t        CMDINVAL            :1;   /*!< bit: 3    Invalid Command Errors: If this bit is set, the block sends an    error interrupt whenever a command is sent with invalid values for    !!COMMAND.SPEED or !!COMMAND.DIRECTION.*/
      uint8_t        UNDERFLOW           :1;   /*!< bit: 2    Underflow Errors: If this bit is set, the block sends an    error interrupt whenever there is a read from !!RXDATA    but the RX FIFO is empty.*/
      uint8_t        OVERFLOW            :1;   /*!< bit: 1    Overflow Errors: If this bit is set, the block sends an    error interrupt whenever the TX FIFO overflows.*/
      uint8_t        CMDBUSY             :1;   /*!< bit: 0    Command Error: If this bit is set, the block sends an error    interrupt whenever a command is issued while busy (i.e. a 1 is    when !!STATUS.READY is not asserted.)*/
      uint32_t       _reserved           :27;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } ERROR_ENABLE;

  union
  {
    struct 
    {
      uint8_t        ACCESSINVAL         :1;   /*!< bit: 5    Indicates that TLUL attempted to write to TXDATA with no bytes enabled. Such    'zero byte' writes are not supported.*/
      uint8_t        CSIDINVAL           :1;   /*!< bit: 4    Indicates a command was attempted with an invalid value for !!CSID.                                 */
      uint8_t        CMDINVAL            :1;   /*!< bit: 3    Indicates an invalid command segment, meaning either an invalid value of    !!COMMAND.SPEED or a request for bidirectional data transfer at dual or quad    speed*/
      uint8_t        UNDERFLOW           :1;   /*!< bit: 2    Indicates that firmware has attempted to read from    !!RXDATA when the RX FIFO is empty.           */
      uint8_t        OVERFLOW            :1;   /*!< bit: 1    Indicates that firmware has overflowed the TX FIFO                                                  */
      uint8_t        CMDBUSY             :1;   /*!< bit: 0    Indicates a write to !!COMMAND when !!STATUS.READY = 0.                                             */
      uint32_t       _reserved           :26;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } ERROR_STATUS;

  union
  {
    struct 
    {
      uint8_t        IDLE                :1;   /*!< bit: 5    Assert to send a spi_event interrupt whenever !!STATUS.ACTIVE    goes low                           */
      uint8_t        READY               :1;   /*!< bit: 4    Assert to send a spi_event interrupt whenever !!STATUS.READY    goes high                           */
      uint8_t        TXWM                :1;   /*!< bit: 3    Assert to send a spi_event interrupt whenever the number of 32-bit words in    the TX FIFO is less than !!CONTROL.TX_WATERMARK.  To prevent the    reassertion of this interrupt add more data to the TX FIFO, or    reduce !!CONTROL.TX_WATERMARK.*/
      uint8_t        RXWM                :1;   /*!< bit: 2    Assert to send a spi_event interrupt whenever the number of 32-bit words in    the RX FIFO is greater than !!CONTROL.RX_WATERMARK. To prevent the    reassertion of this interrupt, read more data from the RX FIFO, or    increase !!CONTROL.RX_WATERMARK.*/
      uint8_t        TXEMPTY             :1;   /*!< bit: 1    Assert to send a spi_event interrupt whenever !!STATUS.TXEMPTY    goes high                         */
      uint8_t        RXFULL              :1;   /*!< bit: 0    Assert to send a spi_event interrupt whenever !!STATUS.RXFULL    goes high                          */
      uint32_t       _reserved           :26;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } EVENT_ENABLE;

} spi_host;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _SPI_HOST_STRUCTS_C_SRC



#endif  /* _SPI_HOST_STRUCTS_C_SRC */

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



#endif /* _SPI_HOST_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
