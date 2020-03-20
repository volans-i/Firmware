/************************************************************************************
 * nuttx-configs/holybro/durandal-v1/include/board.h
 *
 *   Copyright (C) 2016-2019 Gregory Nutt. All rights reserved.
 *   Authors: David Sidrane <david.sidrane@nscdg.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/
#ifndef __NUTTX_CONFIG_HEX_CUBEORANGE_INCLUDE_BOARD_H
#define __NUTTX_CONFIG_HEX_CUBEORANGE_INCLUDE_BOARD_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
# include <stdint.h>
#endif

#include "stm32_rcc.h"
#include "stm32_sdmmc.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/* Clocking *************************************************************************/
/* The Hex/ProfiCNC CubeOrange board provides the following clock sources:
 *
 *   X1: 24 MHz crystal for HSE
 *
 * So we have these clock source available within the STM32
 *
 *   HSI: 16 MHz RC factory-trimmed
 *   HSE: 24 MHz crystal for HSE
 */

#define STM32_BOARD_XTAL        24000000ul

#define STM32_HSI_FREQUENCY     16000000ul
#define STM32_HSE_FREQUENCY     STM32_BOARD_XTAL
#define STM32_LSI_FREQUENCY     32000
#define STM32_LSE_FREQUENCY     32768

/* Main PLL Configuration.
 *
 * PLL source is HSE = 24,000,000
 *
 * PLL_VCOx = (STM32_HSE_FREQUENCY / PLLM) * PLLN
 * Subject to:
 *
 *     1 <= PLLM <= 63
 *     4 <= PLLN <= 512
 *   150 MHz <= PLL_VCOL <= 420MHz
 *   192 MHz <= PLL_VCOH <= 836MHz
 *
 * SYSCLK  = PLL_VCO / PLLP
 * CPUCLK  = SYSCLK / D1CPRE
 * Subject to
 *
 *   PLLP1   = {2, 4, 6, 8, ..., 128}
 *   PLLP2,3 = {2, 3, 4, ..., 128}
 *   CPUCLK <= 480 MHz
 */

#define STM32_BOARD_USEHSE

#define STM32_PLLCFG_PLLSRC      RCC_PLLCKSELR_PLLSRC_HSE

/* PLL1, wide 4 - 8 MHz input, enable DIVP, DIVQ, DIVR
 *
 *   PLL1_VCO = (24,000,000 / 3) * 100 = 800 MHz
 *
 *   PLL1P = PLL1_VCO/2  = 800 MHz / 2   = 400 MHz
 *   PLL1Q = PLL1_VCO/8  = 800 MHz / 8   = 100 MHz
 *   PLL1R = PLL1_VCO/2  = 800 MHz / 2   = 400 MHz
 */

// Adapted From: ArduPilot/libraries/AP_HAL_ChibiOS/hwdef/common/stm32h7_mcuconf.h

// this gives 400MHz system clock
#define _PLL1_DIVM               3
#define _PLL2_DIVM               3
#define _PLL3_DIVM               6

#define _PLL1_DIVN               100
#define _PLL1_DIVP               2
#define _PLL1_DIVQ               8
#define _PLL1_DIVR               2

#define _PLL2_DIVN               25
#define _PLL2_DIVP               2
#define _PLL2_DIVQ               2
#define _PLL2_DIVR               2

#define _PLL3_DIVN               72
#define _PLL3_DIVP               3
#define _PLL3_DIVQ               6
#define _PLL3_DIVR               9

#define STM32_PLLCFG_PLL1CFG    (RCC_PLLCFGR_PLL1VCOSEL_WIDE | \
				 RCC_PLLCFGR_PLL1RGE_4_8_MHZ | \
				 RCC_PLLCFGR_DIVP1EN | \
				 RCC_PLLCFGR_DIVQ1EN | \
				 RCC_PLLCFGR_DIVR1EN)
#define STM32_PLLCFG_PLL1M       RCC_PLLCKSELR_DIVM1(_PLL1_DIVM)
#define STM32_PLLCFG_PLL1N       RCC_PLL1DIVR_N1(_PLL1_DIVN)
#define STM32_PLLCFG_PLL1P       RCC_PLL1DIVR_P1(_PLL1_DIVP)
#define STM32_PLLCFG_PLL1Q       RCC_PLL1DIVR_Q1(_PLL1_DIVQ)
#define STM32_PLLCFG_PLL1R       RCC_PLL1DIVR_R1(_PLL1_DIVR)

#define STM32_VCO1_FREQUENCY     ((STM32_HSE_FREQUENCY / _PLL1_DIVM) * _PLL1_DIVN)
#define STM32_PLL1P_FREQUENCY    (STM32_VCO1_FREQUENCY / _PLL1_DIVP)
#define STM32_PLL1Q_FREQUENCY    (STM32_VCO1_FREQUENCY / _PLL1_DIVQ)
#define STM32_PLL1R_FREQUENCY    (STM32_VCO1_FREQUENCY / _PLL1_DIVR)

/* PLL2 */

#define STM32_PLLCFG_PLL2CFG     (RCC_PLLCFGR_PLL2VCOSEL_WIDE | \
				  RCC_PLLCFGR_PLL2RGE_4_8_MHZ | \
				  RCC_PLLCFGR_DIVP2EN | \
				  RCC_PLLCFGR_DIVQ2EN | \
				  RCC_PLLCFGR_DIVR2EN)
#define STM32_PLLCFG_PLL2M       RCC_PLLCKSELR_DIVM2(_PLL2_DIVM)
#define STM32_PLLCFG_PLL2N       RCC_PLL2DIVR_N2(_PLL2_DIVN)
#define STM32_PLLCFG_PLL2P       RCC_PLL2DIVR_P2(_PLL2_DIVP)
#define STM32_PLLCFG_PLL2Q       RCC_PLL2DIVR_Q2(_PLL2_DIVQ)
#define STM32_PLLCFG_PLL2R       RCC_PLL2DIVR_R2(_PLL2_DIVR)

#define STM32_VCO2_FREQUENCY     ((STM32_HSE_FREQUENCY / _PLL2_DIVM) * _PLL2_DIVN)
#define STM32_PLL2P_FREQUENCY    (STM32_VCO2_FREQUENCY / _PLL2_DIVP)
#define STM32_PLL2Q_FREQUENCY    (STM32_VCO2_FREQUENCY / _PLL2_DIVQ)
#define STM32_PLL2R_FREQUENCY    (STM32_VCO2_FREQUENCY / _PLL2_DIVR)

/* PLL3 */

#define STM32_PLLCFG_PLL3CFG    (RCC_PLLCFGR_PLL3VCOSEL_WIDE | \
				 RCC_PLLCFGR_PLL3RGE_4_8_MHZ | \
				 RCC_PLLCFGR_DIVQ3EN)
#define STM32_PLLCFG_PLL3M      RCC_PLLCKSELR_DIVM3(_PLL3_DIVM)
#define STM32_PLLCFG_PLL3N      RCC_PLL3DIVR_N3(_PLL3_DIVN)
#define STM32_PLLCFG_PLL3P      RCC_PLL3DIVR_P3(_PLL3_DIVP)
#define STM32_PLLCFG_PLL3Q      RCC_PLL3DIVR_Q3(_PLL3_DIVQ)
#define STM32_PLLCFG_PLL3R      RCC_PLL3DIVR_R3(_PLL3_DIVR)

#define STM32_VCO3_FREQUENCY    ((STM32_HSE_FREQUENCY / _PLL3_DIVM) * _PLL3_DIVN)
#define STM32_PLL3P_FREQUENCY   (STM32_VCO3_FREQUENCY / _PLL3_DIVP)
#define STM32_PLL3Q_FREQUENCY   (STM32_VCO3_FREQUENCY / _PLL3_DIVQ)
#define STM32_PLL3R_FREQUENCY   (STM32_VCO3_FREQUENCY / _PLL3_DIVR)

/* SYSCLK = PLL1P = 400MHz
 * CPUCLK = SYSCLK / 1 = 400 MHz
 */

#define STM32_RCC_D1CFGR_D1CPRE  (RCC_D1CFGR_D1CPRE_SYSCLK)
#define STM32_SYSCLK_FREQUENCY   (STM32_PLL1P_FREQUENCY)
#define STM32_CPUCLK_FREQUENCY   (STM32_SYSCLK_FREQUENCY / 1)

/* Configure Clock Assignments */

/* AHB clock (HCLK) is SYSCLK/4 (240 MHz max)
 * HCLK1 = HCLK2 = HCLK3 = HCLK4 = 200
 */

#define STM32_RCC_D1CFGR_HPRE   RCC_D1CFGR_HPRE_SYSCLKd2        /* HCLK  = SYSCLK / 2 */
#define STM32_ACLK_FREQUENCY    (STM32_CPUCLK_FREQUENCY / 2)    /* ACLK in D1, HCLK3 in D1 */
#define STM32_HCLK_FREQUENCY    (STM32_CPUCLK_FREQUENCY / 2)    /* HCLK in D2, HCLK4 in D3 */
#define STM32_BOARD_HCLK        STM32_HCLK_FREQUENCY            /* same as above, to satisfy compiler */

/* APB1 clock (PCLK1) is HCLK/2 (100 MHz) */

#define STM32_RCC_D2CFGR_D2PPRE1  RCC_D2CFGR_D2PPRE1_HCLKd2       /* PCLK1 = HCLK / 2 */
#define STM32_PCLK1_FREQUENCY     (STM32_HCLK_FREQUENCY/2)

/* APB2 clock (PCLK2) is HCLK/2 (100 MHz) */

#define STM32_RCC_D2CFGR_D2PPRE2  RCC_D2CFGR_D2PPRE2_HCLKd2       /* PCLK2 = HCLK / 2 */
#define STM32_PCLK2_FREQUENCY     (STM32_HCLK_FREQUENCY/2)

/* APB3 clock (PCLK3) is HCLK/2 (100 MHz) */

#define STM32_RCC_D1CFGR_D1PPRE   RCC_D1CFGR_D1PPRE_HCLKd2        /* PCLK3 = HCLK / 2 */
#define STM32_PCLK3_FREQUENCY     (STM32_HCLK_FREQUENCY/2)

/* APB4 clock (PCLK4) is HCLK/4 (100 MHz) */

#define STM32_RCC_D3CFGR_D3PPRE   RCC_D3CFGR_D3PPRE_HCLKd2       /* PCLK4 = HCLK / 2 */
#define STM32_PCLK4_FREQUENCY     (STM32_HCLK_FREQUENCY/2)

/* Timer clock frequencies */

/* Timers driven from APB1 will be twice PCLK1 */
/// JC TODO
#define STM32_APB1_TIM2_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM3_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM4_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM5_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM6_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM7_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM12_CLKIN  (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM13_CLKIN  (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM14_CLKIN  (2*STM32_PCLK1_FREQUENCY)

/* Timers driven from APB2 will be twice PCLK2 */
/// JC TODO
#define STM32_APB2_TIM1_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM8_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM15_CLKIN  (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM16_CLKIN  (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM17_CLKIN  (2*STM32_PCLK2_FREQUENCY)

/* Kernel Clock Configuration
 *
 * Note: look at Table 54 in ST Manual
 */

/* I2C123 clock source: PLL3 */

#define STM32_RCC_D2CCIP2R_I2C123SRC RCC_D2CCIP2R_I2C123SEL_PLL3

/* I2C4 clock source */
/// [JC] Unused, so ok?
// #define STM32_RCC_D3CCIPR_I2C4SRC    RCC_D3CCIPR_I2C4SEL_PLL3

/* SPI123 clock source */

#define STM32_RCC_D2CCIP1R_SPI123SRC RCC_D2CCIP1R_SPI123SEL_PLL1

/* SPI45 clock source */

#define STM32_RCC_D2CCIP1R_SPI45SRC  RCC_D2CCIP1R_SPI45SEL_PLL2

/* SPI6 clock source */
/// [JC] Unused, so ok?
// #define STM32_RCC_D3CCIPR_SPI6SRC    RCC_D3CCIPR_SPI6SEL_PLL2

/* USB 1 and 2 clock source */

#define STM32_RCC_D2CCIP2R_USBSRC    RCC_D2CCIP2R_USBSEL_PLL3

/* ADC 1 2 3 clock source */

#define STM32_RCC_D3CCIPR_ADCSEL     RCC_D3CCIPR_ADCSEL_PLL3

/* FLASH wait states
 *
 *  ------------ ---------- -----------
 *  Vcore        MAX ACLK   WAIT STATES
 *  ------------ ---------- -----------
 *  1.15-1.26 V     70 MHz    0
 *  (VOS1 level)   140 MHz    1
 *                 210 MHz    2
 *  1.05-1.15 V     55 MHz    0
 *  (VOS2 level)   110 MHz    1
 *                 165 MHz    2
 *                 220 MHz    3
 *  0.95-1.05 V     45 MHz    0
 *  (VOS3 level)    90 MHz    1
 *                 135 MHz    2
 *                 180 MHz    3
 *                 225 MHz    4
 *  ------------ ---------- -----------
 */
/// JC TODO
#define BOARD_FLASH_WAITSTATES 2

/* SDMMC definitions ********************************************************/
/// JC TODO
/* Init 400kHz, freq = PLL1Q/(2*div)  div =  PLL1Q/(2*freq) */

#define STM32_SDMMC_INIT_CLKDIV     (300 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)

/* 25 MHz Max for now, 25 mHZ = PLL1Q/(2*div), div =  PLL1Q/(2*freq)
 * div = 4.8 = 240 / 50, So round up to 5 for default speed 24 MB/s
 */
/// JC TODO
#if defined(CONFIG_STM32H7_SDMMC_XDMA) || defined(CONFIG_STM32H7_SDMMC_IDMA)
#  define STM32_SDMMC_MMCXFR_CLKDIV   (5 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#else
#  define STM32_SDMMC_MMCXFR_CLKDIV   (100 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#endif
#if defined(CONFIG_STM32H7_SDMMC_XDMA) || defined(CONFIG_STM32H7_SDMMC_IDMA)
#  define STM32_SDMMC_SDXFR_CLKDIV    (5 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#else
#  define STM32_SDMMC_SDXFR_CLKDIV    (100 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#endif

#define STM32_SDMMC_CLKCR_EDGE      STM32_SDMMC_CLKCR_NEGEDGE

/* LED definitions ******************************************************************/
/* The holybro durandal v1 board has three, LED_GREEN a Green LED, LED_BLUE
 * a Blue LED and LED_RED a Red LED, that can be controlled by software.
 *
 * If CONFIG_ARCH_LEDS is not defined, then the user can control the LEDs in any way.
 * The following definitions are used to access individual LEDs.
 */

/* LED index values for use with board_userled() */
/// JC TODO
#define BOARD_LED1        0
#define BOARD_LED2        1
#define BOARD_LED3        2
#define BOARD_NLEDS       3

#define BOARD_LED_RED     BOARD_LED1
#define BOARD_LED_GREEN   BOARD_LED2
#define BOARD_LED_BLUE    BOARD_LED3

/* LED bits for use with board_userled_all() */

#define BOARD_LED1_BIT    (1 << BOARD_LED1)
#define BOARD_LED2_BIT    (1 << BOARD_LED2)
#define BOARD_LED3_BIT    (1 << BOARD_LED3)

/* If CONFIG_ARCH_LEDS is defined, the usage by the board port is defined in
 * include/board.h and src/stm32_leds.c. The LEDs are used to encode OS-related
 * events as follows:
 *
 *
 *   SYMBOL                     Meaning                      LED state
 *                                                        Red   Green Blue
 *   ----------------------  --------------------------  ------ ------ ----*/

#define LED_STARTED        0 /* NuttX has been started   OFF    OFF   OFF  */
#define LED_HEAPALLOCATE   1 /* Heap has been allocated  OFF    OFF   ON   */
#define LED_IRQSENABLED    2 /* Interrupts enabled       OFF    ON    OFF  */
#define LED_STACKCREATED   3 /* Idle stack created       OFF    ON    ON   */
#define LED_INIRQ          4 /* In an interrupt          N/C    N/C   GLOW */
#define LED_SIGNAL         5 /* In a signal handler      N/C    GLOW  N/C  */
#define LED_ASSERTION      6 /* An assertion failed      GLOW   N/C   GLOW */
#define LED_PANIC          7 /* The system has crashed   Blink  OFF   N/C  */
#define LED_IDLE           8 /* MCU is is sleep mode     ON     OFF   OFF  */

/* Thus if the Green LED is statically on, NuttX has successfully booted and
 * is, apparently, running normally.  If the Red LED is flashing at
 * approximately 2Hz, then a fatal error has been detected and the system
 * has halted.
 */

/* Alternate function pin selections ************************************************/

// Telem1 / Serial2 [APM] | ttyS0
#define GPIO_USART2_RX   GPIO_USART2_RX_2      /* PD6 */
#define GPIO_USART2_TX   GPIO_USART2_TX_2      /* PD5 */
#define GPIO_USART2_RTS  GPIO_USART2_RTS_2     /* PD4 */
#define GPIO_USART2_CTS  GPIO_USART2_CTS_NSS_2 /* PD3 */

// Telem2 / Serial3 [APM] | ttyS1
#define GPIO_USART3_RX   GPIO_USART3_RX_3      /* PD9  */
#define GPIO_USART3_TX   GPIO_USART3_TX_3      /* PD8  */
#define GPIO_USART3_RTS  GPIO_USART3_RTS_2     /* PD12 */
#define GPIO_USART3_CTS  GPIO_USART3_CTS_NSS_2 /* PD11 */

// GPS1 / Serial1 [APM] | ttyS2
#define GPIO_UART4_RX    GPIO_UART4_RX_2       /* PA1 */
#define GPIO_UART4_TX    GPIO_UART4_TX_2       /* PA0 */

// USART to IO MCU | ttyS3
#define GPIO_USART6_RX   GPIO_USART6_RX_1      /* PC7  */
#define GPIO_USART6_TX   GPIO_USART6_TX_1      /* PC6 */

// NuttX nsh Console |  ttyS4
#define GPIO_UART7_RX    GPIO_UART7_RX_3       /* PE7 */
#define GPIO_UART7_TX    GPIO_UART7_TX_3       /* PE8 */

// GPS2 / Serial4 [APM] | ttyS5
#define GPIO_UART8_RX    GPIO_UART8_RX_1       /* PE0 */
#define GPIO_UART8_TX    GPIO_UART8_TX_1       /* PE1 */

/* UART RX DMA configurations */
/// [JC] No DMA on UART8
/// [JC] We're using it on USART6 instead
#define DMAMAP_USART6_RX         DMAMAP_DMA12_USART6RX_0 /* DMA1:81 */
#define DMAMAP_USART6_TX         DMAMAP_DMA12_USART6TX_0 /* DMA1:82 */

/* CAN
 *
 * CAN1 is routed to transceiver.
 * CAN2 is routed to transceiver.
 */
#define GPIO_CAN1_RX     GPIO_CAN1_RX_3        /* PD0  */
#define GPIO_CAN1_TX     GPIO_CAN1_TX_3        /* PD1 */
#define GPIO_CAN2_RX     GPIO_CAN2_RX_1        /* PB12 */
#define GPIO_CAN2_TX     GPIO_CAN2_TX_2        /* PB6 */

/* SPI
 * SPI1 internal sensors
 * SPI2 is FRAM.
 * SPI4 is external sensors
 */

#define GPIO_SPI1_SCK    GPIO_SPI1_SCK_1    /* PA5 */
#define GPIO_SPI1_MISO   GPIO_SPI1_MISO_1   /* PA6 */
#define GPIO_SPI1_MOSI   GPIO_SPI1_MOSI_1   /* PA7 */

#define GPIO_SPI2_SCK    GPIO_SPI2_SCK_4    /* PB13 */
#define GPIO_SPI2_MISO   GPIO_SPI2_MISO_1   /* PB14 */
#define GPIO_SPI2_MOSI   GPIO_SPI2_MOSI_1   /* PB15 */

#define GPIO_SPI4_SCK    GPIO_SPI4_SCK_2    /* PE2 */
#define GPIO_SPI4_MISO   GPIO_SPI4_MISO_2   /* PE5 */
#define GPIO_SPI4_MOSI   GPIO_SPI4_MOSI_2   /* PE6 */

/* I2C
 *
 *   Each I2C is associated with a U[S]ART
 *   hence the naming I2C2_SDA_UART4 in FMU USAGE spreadsheet
 *
 *   The optional _GPIO configurations allow the I2C driver to manually
 *   reset the bus to clear stuck slaves.  They match the pin configuration,
 *   but are normally-high GPIOs.
 *
 */

#define GPIO_I2C1_SCL GPIO_I2C1_SCL_2       /* PB8  */
#define GPIO_I2C1_SDA GPIO_I2C1_SDA_2       /* PB9  */

#define GPIO_I2C1_SCL_GPIO                  (GPIO_OUTPUT | GPIO_OPENDRAIN |GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTB | GPIO_PIN8)
#define GPIO_I2C1_SDA_GPIO                  (GPIO_OUTPUT | GPIO_OPENDRAIN |GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTB | GPIO_PIN9)

#define GPIO_I2C2_SCL GPIO_I2C2_SCL_1       /* PB10 */
#define GPIO_I2C2_SDA GPIO_I2C2_SDA_1       /* PB11 */

#define GPIO_I2C2_SCL_GPIO                  (GPIO_OUTPUT | GPIO_OPENDRAIN |GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTB | GPIO_PIN10)
#define GPIO_I2C2_SDA_GPIO                  (GPIO_OUTPUT | GPIO_OPENDRAIN |GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTB | GPIO_PIN11)

/* SDMMC1
 *
 *      VDD 3.3
 *      GND
 *      SDMMC1_CK                           PC12
 *      SDMMC1_CMD                          PD2
 *      SDMMC1_D0                           PC8
 *      SDMMC1_D1                           PC9
 *      SDMMC1_D2                           PC10
 *      SDMMC1_D3                           PC11
 *      GPIO_SDMMC1_NCD                     PG0
 */

/* USB
 *
 *      OTG_FS_DM                           PA11
 *      OTG_FS_DP                           PA12
 *      VBUS                                PA9
 */


/* Board provides GPIO or other Hardware for signaling to timing analyzer */

// #if defined(CONFIG_BOARD_USE_PROBES)
// # include "stm32_gpio.h"
// # define PROBE_N(n) (1<<((n)-1))
// # define PROBE_1    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN14)  /* PE14 AUX1 */
// # define PROBE_2    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTA|GPIO_PIN10)  /* PA10 AUX2 */
// # define PROBE_3    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN11)  /* PE11 AUX3 */
// # define PROBE_4    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN9)   /* PE9  AUX4 */
// # define PROBE_5    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTD|GPIO_PIN13)  /* PD13 AUX5 */
// # define PROBE_6    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTD|GPIO_PIN14)  /* PD14 FMU_CAP6 */
// # define PROBE_7    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTH|GPIO_PIN6)   /* PH6  FMU_CAP5 */
// # define PROBE_8    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTH|GPIO_PIN9)   /* PH9  FMU_CAP4 */
// # define PROBE_9    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTA|GPIO_PIN5)   /* PA5  FMU_CAP3 */
// # define PROBE_10   (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTB|GPIO_PIN3)   /* PB3  FMU_CAP2 */
// # define PROBE_11   (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTB|GPIO_PIN11)  /* PB11 FMU_CAP1 */

// # define PROBE_INIT(mask) \
// 	do { \
// 		if ((mask)& PROBE_N(1)) { stm32_configgpio(PROBE_1); } \
// 		if ((mask)& PROBE_N(2)) { stm32_configgpio(PROBE_2); } \
// 		if ((mask)& PROBE_N(3)) { stm32_configgpio(PROBE_3); } \
// 		if ((mask)& PROBE_N(4)) { stm32_configgpio(PROBE_4); } \
// 		if ((mask)& PROBE_N(5)) { stm32_configgpio(PROBE_5); } \
// 		if ((mask)& PROBE_N(6)) { stm32_configgpio(PROBE_6); } \
// 		if ((mask)& PROBE_N(7)) { stm32_configgpio(PROBE_7); } \
// 		if ((mask)& PROBE_N(8)) { stm32_configgpio(PROBE_8); } \
// 		if ((mask)& PROBE_N(9)) { stm32_configgpio(PROBE_9); } \
// 		if ((mask)& PROBE_N(10)) { stm32_configgpio(PROBE_10); } \
// 		if ((mask)& PROBE_N(11)) { stm32_configgpio(PROBE_11); } \
// 	} while(0)

// # define PROBE(n,s)  do {stm32_gpiowrite(PROBE_##n,(s));}while(0)
// # define PROBE_MARK(n) PROBE(n,false);PROBE(n,true)
// #else
# define PROBE_INIT(mask)
# define PROBE(n,s)
# define PROBE_MARK(n)
// #endif

/************************************************************************************
 * Public Data
 ************************************************************************************/
#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/

/************************************************************************************
 * Name: stm32_boardinitialize
 *
 * Description:
 *   All STM32 architectures must provide the following entry point.  This entry point
 *   is called early in the initialization -- after all memory has been configured
 *   and mapped but before any devices have been initialized.
 *
 ************************************************************************************/

void stm32_boardinitialize(void);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif  /*__NUTTX_CONFIG_HEX_CUBEORANGE_INCLUDE_BOARD_H  */
