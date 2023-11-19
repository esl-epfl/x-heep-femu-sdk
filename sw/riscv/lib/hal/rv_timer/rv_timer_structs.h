/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : rv_timer_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   rv_timer_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _RV_TIMER_STRUCTS_H
#define RV_TIMER_STRUCTS

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
      uint8_t        active              :1;   /*!< bit: 0    If 1, timer operates                                                                                */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CTRL;

  union
  {
    struct 
    {
      uint16_t       prescale            :12;  /*!< bit: 11:0 Prescaler to generate tick                                                                          */
      uint8_t        step                :8;   /*!< bit: 23:16Incremental value for each tick                                                                     */
      uint16_t       _reserved           :12;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CFG0;

  union
  {
    struct 
    {
      uint32_t       v                   :32;  /*!< bit: 31:0 Timer value [31:0]                                                                                  */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMER_V_LOWER0;

  union
  {
    struct 
    {
      uint32_t       v                   :32;  /*!< bit: 31:0 Timer value [63:32]                                                                                 */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMER_V_UPPER0;

  union
  {
    struct 
    {
      uint32_t       v                   :32;  /*!< bit: 31:0 Timer compare value [31:0]                                                                          */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } COMPARE_LOWER0_0;

  union
  {
    struct 
    {
      uint32_t       v                   :32;  /*!< bit: 31:0 Timer compare value [63:32]                                                                         */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } COMPARE_UPPER0_0;

  union
  {
    struct 
    {
      uint8_t        IE                  :1;   /*!< bit: 0    Interrupt Enable for timer                                                                          */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTR_ENABLE0;

  union
  {
    struct 
    {
      uint8_t        IS                  :1;   /*!< bit: 0    Interrupt status for timer                                                                          */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTR_STATE0;

  union
  {
    struct 
    {
      uint8_t        T                   :1;   /*!< bit: 0    Interrupt test for timer                                                                            */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTR_TEST0;

  union
  {
    struct 
    {
      uint16_t       prescale            :12;  /*!< bit: 11:0 Prescaler to generate tick                                                                          */
      uint8_t        step                :8;   /*!< bit: 23:16Incremental value for each tick                                                                     */
      uint16_t       _reserved           :12;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CFG1;

  union
  {
    struct 
    {
      uint32_t       v                   :32;  /*!< bit: 31:0 Timer value [31:0]                                                                                  */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMER_V_LOWER1;

  union
  {
    struct 
    {
      uint32_t       v                   :32;  /*!< bit: 31:0 Timer value [63:32]                                                                                 */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } TIMER_V_UPPER1;

  union
  {
    struct 
    {
      uint32_t       v                   :32;  /*!< bit: 31:0 Timer compare value [31:0]                                                                          */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } COMPARE_LOWER1_0;

  union
  {
    struct 
    {
      uint32_t       v                   :32;  /*!< bit: 31:0 Timer compare value [63:32]                                                                         */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } COMPARE_UPPER1_0;

  union
  {
    struct 
    {
      uint8_t        IE                  :1;   /*!< bit: 0    Interrupt Enable for timer                                                                          */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTR_ENABLE1;

  union
  {
    struct 
    {
      uint8_t        IS                  :1;   /*!< bit: 0    Interrupt status for timer                                                                          */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTR_STATE1;

  union
  {
    struct 
    {
      uint8_t        T                   :1;   /*!< bit: 0    Interrupt test for timer                                                                            */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTR_TEST1;

} rv_timer;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _RV_TIMER_STRUCTS_C_SRC



#endif  /* _RV_TIMER_STRUCTS_C_SRC */

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



#endif /* _RV_TIMER_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
