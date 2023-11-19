/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : soc_ctrl_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   soc_ctrl_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _SOC_CTRL_STRUCTS_H
#define SOC_CTRL_STRUCTS

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
      uint8_t        EXIT_VALID          :1;   /*!< bit: 0    Exit Valid Reg                                                                                      */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } EXIT_VALID;

  union
  {
    struct 
    {
      uint32_t       EXIT_VALUE          :32;  /*!< bit: 31:0 Exit Value Reg                                                                                      */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } EXIT_VALUE;

  union
  {
    struct 
    {
      uint8_t        BOOT_SELECT         :1;   /*!< bit: 0    Boot Select Reg                                                                                     */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } BOOT_SELECT;

  union
  {
    struct 
    {
      uint8_t        BOOT_EXIT_LOOP      :1;   /*!< bit: 0    Boot Exit Reg                                                                                       */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } BOOT_EXIT_LOOP;

  union
  {
    struct 
    {
      uint32_t       BOOT_ADDRESS        :32;  /*!< bit: 31:0 Boot Address Reg                                                                                    */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } BOOT_ADDRESS;

  union
  {
    struct 
    {
      uint8_t        USE_SPIMEMIO        :1;   /*!< bit: 0    Spi Select Reg                                                                                      */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } USE_SPIMEMIO;

  union
  {
    struct 
    {
      uint8_t        ENABLE_SPI_SEL      :1;   /*!< bit: 0    Enable Spi Select Reg                                                                               */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } ENABLE_SPI_SEL;

  union
  {
    struct 
    {
      uint32_t       SYSTEM_FREQUENCY_HZ :32;  /*!< bit: 31:0 Contains the value in Hz of the frequency the system is running                                     */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } SYSTEM_FREQUENCY_HZ;

} soc_ctrl;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _SOC_CTRL_STRUCTS_C_SRC



#endif  /* _SOC_CTRL_STRUCTS_C_SRC */

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



#endif /* _SOC_CTRL_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
