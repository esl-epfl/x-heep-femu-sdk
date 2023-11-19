/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : rv_plic_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   rv_plic_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _RV_PLIC_STRUCTS_H
#define RV_PLIC_STRUCTS

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
      uint8_t        P                   :1;   /*!< bit: 0    Interrupt Pending of Source                                                                         */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } IP;

  union
  {
    struct 
    {
      uint8_t        LE                  :1;   /*!< bit: 0    L0E1                                                                                                */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } LE;

  union
  {
    struct 
    {
      uint8_t        PRIO0               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO0;

  union
  {
    struct 
    {
      uint8_t        PRIO1               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO1;

  union
  {
    struct 
    {
      uint8_t        PRIO2               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO2;

  union
  {
    struct 
    {
      uint8_t        PRIO3               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO3;

  union
  {
    struct 
    {
      uint8_t        PRIO4               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO4;

  union
  {
    struct 
    {
      uint8_t        PRIO5               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO5;

  union
  {
    struct 
    {
      uint8_t        PRIO6               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO6;

  union
  {
    struct 
    {
      uint8_t        PRIO7               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO7;

  union
  {
    struct 
    {
      uint8_t        PRIO8               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO8;

  union
  {
    struct 
    {
      uint8_t        PRIO9               :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO9;

  union
  {
    struct 
    {
      uint8_t        PRIO10              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO10;

  union
  {
    struct 
    {
      uint8_t        PRIO11              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO11;

  union
  {
    struct 
    {
      uint8_t        PRIO12              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO12;

  union
  {
    struct 
    {
      uint8_t        PRIO13              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO13;

  union
  {
    struct 
    {
      uint8_t        PRIO14              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO14;

  union
  {
    struct 
    {
      uint8_t        PRIO15              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO15;

  union
  {
    struct 
    {
      uint8_t        PRIO16              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO16;

  union
  {
    struct 
    {
      uint8_t        PRIO17              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO17;

  union
  {
    struct 
    {
      uint8_t        PRIO18              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO18;

  union
  {
    struct 
    {
      uint8_t        PRIO19              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO19;

  union
  {
    struct 
    {
      uint8_t        PRIO20              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO20;

  union
  {
    struct 
    {
      uint8_t        PRIO21              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO21;

  union
  {
    struct 
    {
      uint8_t        PRIO22              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO22;

  union
  {
    struct 
    {
      uint8_t        PRIO23              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO23;

  union
  {
    struct 
    {
      uint8_t        PRIO24              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO24;

  union
  {
    struct 
    {
      uint8_t        PRIO25              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO25;

  union
  {
    struct 
    {
      uint8_t        PRIO26              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO26;

  union
  {
    struct 
    {
      uint8_t        PRIO27              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO27;

  union
  {
    struct 
    {
      uint8_t        PRIO28              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO28;

  union
  {
    struct 
    {
      uint8_t        PRIO29              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO29;

  union
  {
    struct 
    {
      uint8_t        PRIO30              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO30;

  union
  {
    struct 
    {
      uint8_t        PRIO31              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO31;

  union
  {
    struct 
    {
      uint8_t        PRIO32              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO32;

  union
  {
    struct 
    {
      uint8_t        PRIO33              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO33;

  union
  {
    struct 
    {
      uint8_t        PRIO34              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO34;

  union
  {
    struct 
    {
      uint8_t        PRIO35              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO35;

  union
  {
    struct 
    {
      uint8_t        PRIO36              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO36;

  union
  {
    struct 
    {
      uint8_t        PRIO37              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO37;

  union
  {
    struct 
    {
      uint8_t        PRIO38              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO38;

  union
  {
    struct 
    {
      uint8_t        PRIO39              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO39;

  union
  {
    struct 
    {
      uint8_t        PRIO40              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO40;

  union
  {
    struct 
    {
      uint8_t        PRIO41              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO41;

  union
  {
    struct 
    {
      uint8_t        PRIO42              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO42;

  union
  {
    struct 
    {
      uint8_t        PRIO43              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO43;

  union
  {
    struct 
    {
      uint8_t        PRIO44              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO44;

  union
  {
    struct 
    {
      uint8_t        PRIO45              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO45;

  union
  {
    struct 
    {
      uint8_t        PRIO46              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO46;

  union
  {
    struct 
    {
      uint8_t        PRIO47              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO47;

  union
  {
    struct 
    {
      uint8_t        PRIO48              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO48;

  union
  {
    struct 
    {
      uint8_t        PRIO49              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO49;

  union
  {
    struct 
    {
      uint8_t        PRIO50              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO50;

  union
  {
    struct 
    {
      uint8_t        PRIO51              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO51;

  union
  {
    struct 
    {
      uint8_t        PRIO52              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO52;

  union
  {
    struct 
    {
      uint8_t        PRIO53              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO53;

  union
  {
    struct 
    {
      uint8_t        PRIO54              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO54;

  union
  {
    struct 
    {
      uint8_t        PRIO55              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO55;

  union
  {
    struct 
    {
      uint8_t        PRIO56              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO56;

  union
  {
    struct 
    {
      uint8_t        PRIO57              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO57;

  union
  {
    struct 
    {
      uint8_t        PRIO58              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO58;

  union
  {
    struct 
    {
      uint8_t        PRIO59              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO59;

  union
  {
    struct 
    {
      uint8_t        PRIO60              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO60;

  union
  {
    struct 
    {
      uint8_t        PRIO61              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO61;

  union
  {
    struct 
    {
      uint8_t        PRIO62              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO62;

  union
  {
    struct 
    {
      uint8_t        PRIO63              :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PRIO63;

  union
  {
    struct 
    {
      uint8_t        E                   :1;   /*!< bit: 0    Interrupt Enable of Source                                                                          */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } IE0;

  union
  {
    struct 
    {
      uint8_t        THRESHOLD0          :3;   
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } THRESHOLD0;

  union
  {
    struct 
    {
      uint8_t        CC0                 :6;   
      uint32_t       _reserved           :26;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } CC0;

  union
  {
    struct 
    {
      uint8_t        MSIP0               :1;   /*!< bit: 0    Software Interrupt Pending register                                                                 */
      uint32_t       _reserved           :31;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } MSIP0;

} RV_PLIC;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _RV_PLIC_STRUCTS_C_SRC



#endif  /* _RV_PLIC_STRUCTS_C_SRC */

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



#endif /* _RV_PLIC_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
