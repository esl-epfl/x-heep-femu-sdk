/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : gpio_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   gpio_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _GPIO_STRUCTS_H
#define GPIO_STRUCTS

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

typedef enum MODE_enum {
  INPUT_ONLY     =  0,                         /*!< The correspondin GPIO acts as an input only.                                                        */
  OUTPUT_ACTIVE  =  1,                         /*!< Actively drive output to 0 or 1                                                                     */
  OPEN_DRAIN0    =  2,                         /*!< Value 1 drives, value 0 enables tristate.                                                           */
  OPEN_DRAIN1    =  3,                         /*!< Value 0 drives, value 1 enables tristate.                                                           */
} MODE_t;



typedef struct {
  union
  {
    struct 
    {
      uint16_t       GPIO_CNT            :10;  /*!< bit: 9:0  Contains the number of GPIOs controlled by this peripheral.                                         */
      uint16_t       VERSION             :10;  /*!< bit: 19:10The version number of the IPs.                                                                      */
      uint16_t       _reserved           :12;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INFO;

  union
  {
    struct 
    {
      uint8_t        GLBL_INTRPT_MODE    :1;   /*!< bit: 0    If 1, keep the interrupt line asserted until all interrupts are cleared. If 0, generate one cycle wide pulse for every interrupt.*/
      uint8_t        PIN_LVL_INTRPT_MODE :1;   /*!< bit: 0    If 1, keep the interrupt line asserted until all interrupts are cleared. If 0, generate one cycle wide pulse for every interrupt.*/
      uint8_t        reserved            :1;   /*!< bit: 1     Reserved for future use                                                                            */
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CFG;

  union
  {
    struct 
    {
      MODE_t         MODE                :2;   /*!< bit: 1:0  Change the IO  mode of the GPIO.                                                                    */
      uint32_t       _reserved           :30;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } GPIO_MODE;

  union
  {
    struct 
    {
      uint8_t        GPIO_EN             :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } GPIO_EN;

  union
  {
    struct 
    {
      uint8_t        GPIO_IN             :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } GPIO_IN;

  union
  {
    struct 
    {
      uint8_t        GPIO_OUT            :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } GPIO_OUT;

  union
  {
    struct 
    {
      uint8_t        GPIO_SET            :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } GPIO_SET;

  union
  {
    struct 
    {
      uint8_t        GPIO_CLEAR          :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } GPIO_CLEAR;

  union
  {
    struct 
    {
      uint8_t        GPIO_TOGGLE         :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } GPIO_TOGGLE;

  union
  {
    struct 
    {
      uint8_t        INTRPT_RISE_EN      :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_RISE_EN;

  union
  {
    struct 
    {
      uint8_t        INTRPT_FALL_EN      :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_FALL_EN;

  union
  {
    struct 
    {
      uint8_t        INTRPT_LVL_HIGH_EN  :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_LVL_HIGH_EN;

  union
  {
    struct 
    {
      uint8_t        INTRPT_LVL_LOW_EN   :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_LVL_LOW_EN;

  union
  {
    struct 
    {
      uint8_t        INTRPT_STATUS       :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_STATUS;

  union
  {
    struct 
    {
      uint8_t        INTRPT_RISE_STATUS  :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_RISE_STATUS;

  union
  {
    struct 
    {
      uint8_t        INTRPT_FALL_STATUS  :1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_FALL_STATUS;

  union
  {
    struct 
    {
      uint8_t        INTRPT_LVL_HIGH_STATUS:1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_LVL_HIGH_STATUS;

  union
  {
    struct 
    {
      uint8_t        INTRPT_LVL_LOW_STATUS:1;   
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } INTRPT_LVL_LOW_STATUS;

} gpio;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _GPIO_STRUCTS_C_SRC



#endif  /* _GPIO_STRUCTS_C_SRC */

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



#endif /* _GPIO_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
