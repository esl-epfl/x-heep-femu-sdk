/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : power_manager_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   power_manager_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _POWER_MANAGER_STRUCTS_H
#define POWER_MANAGER_STRUCTS

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
      uint8_t        WAKEUP_STATE        :1;   /*!< bit: 0    Wake-up state Reg, used by BOOTROM                                                                  */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } WAKEUP_STATE;

  union
  {
    struct 
    {
      uint32_t       RESTORE_XDDRESS     :32;  /*!< bit: 31:0 Restore xddress Reg, used by BOOTROM                                                                */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RESTORE_ADDRESS;

  union
  {
    struct 
    {
      uint32_t       EN_WAIT_FOR_INTR    :32;  /*!< bit: 31:0 Enable wait for interrupt                                                                           */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } EN_WAIT_FOR_INTR;

  union
  {
    struct 
    {
      uint32_t       INTR_STATE          :32;  /*!< bit: 31:0 Interrupt state Reg                                                                                 */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTR_STATE;

  union
  {
    struct 
    {
      uint8_t        POWER_GATE_CORE     :1;   /*!< bit: 0    Power Gate Core Reg                                                                                 */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } POWER_GATE_CORE;

  union
  {
    struct 
    {
      uint8_t        POWER_GATE_CORE_ACK :1;   /*!< bit: 0    Power Gate Core Ack Reg                                                                             */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } POWER_GATE_CORE_ACK;

  union
  {
    struct 
    {
      uint32_t       CPU_RESET_ASSERT_COUNTER:32;  /*!< bit: 31:0 CPU counter before resetting                                                                        */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CPU_RESET_ASSERT_COUNTER;

  union
  {
    struct 
    {
      uint32_t       CPU_RESET_DEASSERT_COUNTER:32;  /*!< bit: 31:0 CPU counter before unresetting                                                                      */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CPU_RESET_DEASSERT_COUNTER;

  union
  {
    struct 
    {
      uint32_t       CPU_SWITCH_OFF_COUNTER:32;  /*!< bit: 31:0 CPU counter before switching off                                                                    */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CPU_SWITCH_OFF_COUNTER;

  union
  {
    struct 
    {
      uint32_t       CPU_SWITCH_ON_COUNTER:32;  /*!< bit: 31:0 CPU counter before switching on                                                                     */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CPU_SWITCH_ON_COUNTER;

  union
  {
    struct 
    {
      uint8_t        CPU_WAIT_ACK_SWITCH_ON_COUNTER:1;   /*!< bit: 0    wait for CPU switch ack before switching on                                                         */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CPU_WAIT_ACK_SWITCH_ON_COUNTER;

  union
  {
    struct 
    {
      uint32_t       CPU_ISO_OFF_COUNTER :32;  /*!< bit: 31:0 CPU counter before setting off isolation                                                            */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CPU_ISO_OFF_COUNTER;

  union
  {
    struct 
    {
      uint32_t       CPU_ISO_ON_COUNTER  :32;  /*!< bit: 31:0 CPU counter before setting on isolation                                                             */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CPU_ISO_ON_COUNTER;

  union
  {
    struct 
    {
      uint8_t        CPU_RESET_ASSERT_STOP_BIT_COUNTER:1;   /*!< bit: 0    Stop the CPU_RESET_ASSERT_COUNTER counter                                                           */
      uint8_t        CPU_RESET_DEASSERT_STOP_BIT_COUNTER:1;   /*!< bit: 1    Stop the CPU_RESET_DEASSERT_COUNTER counter                                                         */
      uint8_t        CPU_SWITCH_OFF_STOP_BIT_COUNTER:1;   /*!< bit: 2    Stop the CPU_SWITCH_OFF_COUNTER counter                                                             */
      uint8_t        CPU_SWITCH_ON_STOP_BIT_COUNTER:1;   /*!< bit: 3    Stop the CPU_SWITCH_ON_COUNTER counter                                                              */
      uint8_t        CPU_ISO_OFF_STOP_BIT_COUNTER:1;   /*!< bit: 4    Stop the CPU_ISO_OFF_COUNTER counter                                                                */
      uint8_t        CPU_ISO_ON_STOP_BIT_COUNTER:1;   /*!< bit: 5    Stop the CPU_ISO_ON_COUNTER counter                                                                 */
      uint32_t       _reserved           :26;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CPU_COUNTERS_STOP;

  union
  {
    struct 
    {
      uint8_t        POWER_GATE_PERIPH_ACK:1;   /*!< bit: 0    Power Gate Periph Ack Reg                                                                           */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } POWER_GATE_PERIPH_ACK;

  union
  {
    struct 
    {
      uint8_t        PERIPH_RESET        :1;   /*!< bit: 0    Reset PERIPH domain                                                                                 */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PERIPH_RESET;

  union
  {
    struct 
    {
      uint8_t        PERIPH_SWITCH       :1;   /*!< bit: 0    Switch off PERIPH domain                                                                            */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PERIPH_SWITCH;

  union
  {
    struct 
    {
      uint8_t        PERIPH_WAIT_ACK_SWITCH_ON:1;   /*!< bit: 0    Wait PERIPH domain switch ack                                                                       */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PERIPH_WAIT_ACK_SWITCH_ON;

  union
  {
    struct 
    {
      uint8_t        PERIPH_ISO          :1;   /*!< bit: 0    Set on isolation of PERIPH domain                                                                   */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PERIPH_ISO;

  union
  {
    struct 
    {
      uint8_t        PERIPH_CLK_GATE     :1;   /*!< bit: 0    Clock-gates the PERIPH domain                                                                       */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PERIPH_CLK_GATE;

  union
  {
    struct 
    {
      uint8_t        RAM_0_CLK_GATE      :1;   /*!< bit: 0    Clock-gates the RAM_0 domain                                                                        */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_0_CLK_GATE;

  union
  {
    struct 
    {
      uint8_t        POWER_GATE_RAM_BLOCK_0_ACK:1;   /*!< bit: 0    Power Gate Ram Block 0 Ack Reg                                                                      */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } POWER_GATE_RAM_BLOCK_0_ACK;

  union
  {
    struct 
    {
      uint8_t        RAM_0_SWITCH        :1;   /*!< bit: 0    Switch off RAM_0 domain                                                                             */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_0_SWITCH;

  union
  {
    struct 
    {
      uint8_t        RAM_0_WAIT_ACK_SWITCH_ON:1;   /*!< bit: 0    Wait RAM_0 domain switch ack                                                                        */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_0_WAIT_ACK_SWITCH_ON;

  union
  {
    struct 
    {
      uint8_t        RAM_0_ISO           :1;   /*!< bit: 0    Set on isolation of RAM_0 domain                                                                    */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_0_ISO;

  union
  {
    struct 
    {
      uint8_t        RAM_0_RETENTIVE     :1;   /*!< bit: 0    Set on retentive mode for RAM_0 domain                                                              */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_0_RETENTIVE;

  union
  {
    struct 
    {
      uint8_t        RAM_1_CLK_GATE      :1;   /*!< bit: 0    Clock-gates the RAM_1 domain                                                                        */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_1_CLK_GATE;

  union
  {
    struct 
    {
      uint8_t        POWER_GATE_RAM_BLOCK_1_ACK:1;   /*!< bit: 0    Power Gate Ram Block 1 Ack Reg                                                                      */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } POWER_GATE_RAM_BLOCK_1_ACK;

  union
  {
    struct 
    {
      uint8_t        RAM_1_SWITCH        :1;   /*!< bit: 0    Switch off RAM_1 domain                                                                             */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_1_SWITCH;

  union
  {
    struct 
    {
      uint8_t        RAM_1_WAIT_ACK_SWITCH_ON:1;   /*!< bit: 0    Wait RAM_1 domain switch ack                                                                        */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_1_WAIT_ACK_SWITCH_ON;

  union
  {
    struct 
    {
      uint8_t        RAM_1_ISO           :1;   /*!< bit: 0    Set on isolation of RAM_1 domain                                                                    */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_1_ISO;

  union
  {
    struct 
    {
      uint8_t        RAM_1_RETENTIVE     :1;   /*!< bit: 0    Set on retentive mode for RAM_1 domain                                                              */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } RAM_1_RETENTIVE;

  union
  {
    struct 
    {
      uint8_t        MONITOR_POWER_GATE_CORE:3;   /*!< bit: 2:0  Monitor Signals Power Gate Core Reg                                                                 */
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MONITOR_POWER_GATE_CORE;

  union
  {
    struct 
    {
      uint8_t        MONITOR_POWER_GATE_PERIPH:3;   /*!< bit: 2:0  Monitor Signals Power Gate Periph Reg                                                               */
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MONITOR_POWER_GATE_PERIPH;

  union
  {
    struct 
    {
      uint8_t        MONITOR_POWER_GATE_RAM_BLOCK_0:2;   /*!< bit: 1:0  Monitor Signals Power Gate Ram Block 0 Reg                                                          */
      uint32_t       _reserved           :30;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MONITOR_POWER_GATE_RAM_BLOCK_0;

  union
  {
    struct 
    {
      uint8_t        MONITOR_POWER_GATE_RAM_BLOCK_1:2;   /*!< bit: 1:0  Monitor Signals Power Gate Ram Block 1 Reg                                                          */
      uint32_t       _reserved           :30;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MONITOR_POWER_GATE_RAM_BLOCK_1;

  union
  {
    struct 
    {
      uint8_t        MASTER_CPU_FORCE_SWITCH_OFF:1;   /*!< bit: 0    Force Core Switch Off Reg, used by JTAG                                                             */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MASTER_CPU_FORCE_SWITCH_OFF;

  union
  {
    struct 
    {
      uint8_t        MASTER_CPU_FORCE_SWITCH_ON:1;   /*!< bit: 0    Force Core Switch On Reg, used by JTAG                                                              */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MASTER_CPU_FORCE_SWITCH_ON;

  union
  {
    struct 
    {
      uint8_t        MASTER_CPU_FORCE_RESET_ASSERT:1;   /*!< bit: 0    Force Core Reset Assert Reg, used by JTAG                                                           */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MASTER_CPU_FORCE_RESET_ASSERT;

  union
  {
    struct 
    {
      uint8_t        MASTER_CPU_FORCE_RESET_DEASSERT:1;   /*!< bit: 0    Force Core Reset Deassert Reg, used by JTAG                                                         */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MASTER_CPU_FORCE_RESET_DEASSERT;

  union
  {
    struct 
    {
      uint8_t        MASTER_CPU_FORCE_ISO_OFF:1;   /*!< bit: 0    Force Core Iso Off Reg, used by JTAG                                                                */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MASTER_CPU_FORCE_ISO_OFF;

  union
  {
    struct 
    {
      uint8_t        MASTER_CPU_FORCE_ISO_ON:1;   /*!< bit: 0    Force Core Iso On Reg, used by JTAG                                                                 */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MASTER_CPU_FORCE_ISO_ON;

} power_manager;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _POWER_MANAGER_STRUCTS_C_SRC



#endif  /* _POWER_MANAGER_STRUCTS_C_SRC */

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



#endif /* _POWER_MANAGER_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
