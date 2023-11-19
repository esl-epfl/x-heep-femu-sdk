/*
                              *******************
******************************* H SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : x-heep                                                       **
** filename : dma_structs.h                                 **
** date     : 15/05/2023                                                      **
**                                                                         **
*****************************************************************************
**                                                                         **
**                                                                         **
*****************************************************************************

*/

/**
* @file   dma_structs.h
* @date   15/05/2023
* @brief  Contains structs for every register
*
* This file contains the structs of the registes of the peripheral.
* Each structure has the various bit fields that can be accessed
* independently.
* 
*/

#ifndef _DMA_STRUCTS_H
#define DMA_STRUCTS

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
      uint32_t       PTR_IN              :32;  /*!< bit: 31:0 Input data pointer (word aligned)                                                                   */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PTR_IN;

  union
  {
    struct 
    {
      uint32_t       PTR_OUT             :32;  /*!< bit: 31:0 Output data pointer (word aligned)                                                                  */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } PTR_OUT;

  union
  {
    struct 
    {
      uint32_t       DMA_START           :32;  /*!< bit: 31:0 DMA counter and start                                                                               */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } DMA_START;

  union
  {
    struct 
    {
      uint32_t       DONE                :32;  /*!< bit: 31:0 Copy done                                                                                           */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } DONE;

  union
  {
    struct 
    {
      uint32_t       SRC_PTR_INC         :32;  /*!< bit: 31:0 Source pointer increment                                                                            */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } SRC_PTR_INC;

  union
  {
    struct 
    {
      uint32_t       DST_PTR_INC         :32;  /*!< bit: 31:0 Destination pointer increment                                                                       */
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } DST_PTR_INC;

  union
  {
    struct 
    {
      uint8_t        SPI_MODE            :3;   /*!< bit: 2:0  Copy/Read from SPI                                                                                  */
      uint32_t       _reserved           :29;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } SPI_MODE;

  union
  {
    struct 
    {
      uint8_t        DATA_TYPE           :2;   /*!< bit: 1:0  Data type                                                                                           */
      uint32_t       _reserved           :30;  
    } b ;                                      /*!< Structure used for bit access                                                                       */
    uint32_t w;                                /*!< Type used for word access                                                                                     */
  } DATA_TYPE;

} dma;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

#ifndef _DMA_STRUCTS_C_SRC



#endif  /* _DMA_STRUCTS_C_SRC */

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



#endif /* _DMA_STRUCTS_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/
