/*
 * main.h
 *
 *  Created on: 	Jun 24, 2021
 *      Author: 	Michael Ly
 *      Details:	Contains information on the internal registers used
 *      			such as how the registers are partitioned
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

typedef struct {                                                        // Address Offset = 0x30;   Reset Value = 0x0010 0000
    uint32_t    gpioa_en        : 1 ;
    uint32_t    gpiob_en        : 1 ;
    uint32_t    gpioc_en        : 1 ;
    uint32_t    gpiod_en        : 1 ;
    uint32_t    gpioe_en        : 1 ;
    uint32_t    gpiof_en        : 1 ;
    uint32_t    gpiog_en        : 1 ;
    uint32_t    gpioh_en        : 1 ;
    uint32_t    gpioi_en        : 1 ;
    uint32_t    gpioj_en        : 1 ;
    uint32_t    gpiok_en        : 1 ;

    uint32_t    reserved1       : 1 ;
    
    uint32_t    crc_en          : 1 ;
    
    uint32_t    reserved2       : 5 ;

    uint32_t    bkp_sram_en     : 1 ;
    
    uint32_t    reserved3       : 1 ;

    uint32_t    ccm_data_ram_en : 1 ;
    uint32_t    dma1_en         : 1 ;
    uint32_t    dma2_en         : 1 ;
    uint32_t    dma2d_en        : 1 ;

    uint32_t    reserved4       : 1 ;

    uint32_t    eth_mac_en      : 1 ;
    uint32_t    eth_mac_tx_en   : 1 ;
    uint32_t    eth_mac_rx_en   : 1 ;
    uint32_t    eth_mac_ptp_en  : 1 ;
    uint32_t    otg_hs_en       : 1 ;
    uint32_t    otg_hs_ulpi_en  : 1 ;

    uint32_t    reserved5       : 1 ;
} RCC_AHB1ENR_t ;



typedef struct {
    uint32_t    pin_0   : 2 ;                        // mode_r_0
    uint32_t    pin_1   : 2 ;
    uint32_t    pin_2   : 2 ;
    uint32_t    pin_3   : 2 ;
    uint32_t    pin_4   : 2 ;
    uint32_t    pin_5   : 2 ;
    uint32_t    pin_6   : 2 ;
    uint32_t    pin_7   : 2 ;
    uint32_t    pin_8   : 2 ;
    uint32_t    pin_9   : 2 ;
    uint32_t    pin_10  : 2 ;
    uint32_t    pin_11  : 2 ;
    uint32_t    pin_12  : 2 ;
    uint32_t    pin_13  : 2 ;
    uint32_t    pin_14  : 2 ;
    uint32_t    pin_15  : 2 ;
} GPIOx_MODER_t ;



typedef struct {
    uint32_t    pin_0       : 1 ;                   // odr0
    uint32_t    pin_1       : 1 ;
    uint32_t    pin_2       : 1 ;
    uint32_t    pin_3       : 1 ;
    uint32_t    pin_4       : 1 ;
    uint32_t    pin_5       : 1 ;
    uint32_t    pin_6       : 1 ;
    uint32_t    pin_7       : 1 ;
    uint32_t    pin_8       : 1 ;
    uint32_t    pin_9       : 1 ;
    uint32_t    pin_10      : 1 ;
    uint32_t    pin_11      : 1 ;
    uint32_t    pin_12      : 1 ;
    uint32_t    pin_13      : 1 ;
    uint32_t    pin_14      : 1 ;
    uint32_t    pin_15      : 1 ;
    uint32_t    reserved    : 16 ;
} GPIOx_ODR_t ;

// SET bits
uint32_t const	SET_CLOCK	= 1 ;
uint32_t const	SET_MODE	= 1 ;
uint32_t const	SET_OUTPUT	= 1 ;


#endif /* MAIN_H_ */
