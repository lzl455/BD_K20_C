/* ----------------------------------------------------------------------------
 * Copyright (c) 2020-2030 OnMicro Limited. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of OnMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -------------------------------------------------------------------------- */

/**
 * @file     drv_senscan.h
 * @brief    SENSCAN Driver
 * @date     1. Nov 2023
 * @author   OnMicro SW Team
 *
 * @defgroup SENSCAN SENSCAN
 * @ingroup  HAL_Driver
 * @brief    SENSCAN Driver.
 * @details  SENSCAN Driver

 * @version
 * Version 1.0
 *  - Initial release
 *
 * @{
 */

#ifndef __DRV_SENSCAN_H
#define __DRV_SENSCAN_H


/*******************************************************************************
 * INCLUDES
 */
#include "RTE_driver.h"
#if (RTE_SENSCAN)
#include "om_driver.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
 * TYPEDEFS
 */
/**
 * @defgroup senscan_data_format_t SENSCAN data format type
 * @{
 */
typedef enum {
    SENSCAN_DATA_FORMAT_8BIT     = 0,  /**< SENSCAN data format 8bit */
    SENSCAN_DATA_FORMAT_12BIT    = 1,  /**< SENSCAN data format 12bit */
    SENSCAN_DATA_FORMAT_16BIT    = 2,  /**< SENSCAN data format 16bit */
} senscan_data_format_t;
/**
 * @}
 */

/**
 * @defgroup senscan_scan_mode_t SENSCAN scan mode type
 * @{
 */
typedef enum {
    SENSCAN_SCAN_MODE_SINGLE        = 0,  /**< SENSCAN single mode */
    SENSCAN_SCAN_MODE_CONTINUOUS    = 1,  /**< SENSCAN continuous mode */
} senscan_scan_mode_t;
/**
 * @}
 */

/**
 * @defgroup senscan_deltaxy_rev_t SENSCAN deltaxy revert type
 * @{
 */
typedef enum {
    SENSCAN_DELTAXY_REV_4_7BIT     = 0,  /**< SENSCAN read upper bit[7:4] is stored in XH, bit[3:0] is stored in YH */
    SENSCAN_DELTAXY_REV_0_3BIT     = 1,  /**< SENSCAN read upper bit[7:4] is stored in YH, bit[3:0] is stored in XH */
} senscan_deltaxy_rev_t;
/**
 * @}
 */

/**
 * @defgroup senscan_resync_high_time_t sclk pull up time for resync
 * @{
 */
typedef enum {
    SENSCAN_RESYNC_HIGH_TIME_1MS    = 0,   /**< Scclk pull up time 1ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_2MS    = 1,   /**< Scclk pull up time 2ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_4MS    = 2,   /**< Scclk pull up time 4ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_6MS    = 3,   /**< Scclk pull up time 6ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_8MS    = 4,   /**< Scclk pull up time 8ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_12MS   = 5,   /**< Scclk pull up time 12ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_16MS   = 6,   /**< Scclk pull up time 16ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_20MS   = 7,   /**< Scclk pull up time 20ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_24MS   = 8,   /**< Scclk pull up time 24ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_32MS   = 9,   /**< Scclk pull up time 32ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_40MS   = 10,  /**< Scclk pull up time 40ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_48MS   = 11,  /**< Scclk pull up time 48ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_64MS   = 12,  /**< Scclk pull up time 64ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_128MS  = 13,  /**< Scclk pull up time 128ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_256MS  = 14,  /**< Scclk pull up time 256ms for resync */
    SENSCAN_RESYNC_HIGH_TIME_512MS  = 15,  /**< Scclk pull up time 512ms for resync */
} senscan_resync_high_time_t;
/**
 * @}
 */

/**
 * @defgroup senscan_resync_low_time_t sclk pull done time for resync
 * @{
 */
typedef enum {
    SENSCAN_RESYNC_LOW_TIME_2US     = 0,   /**< Sclk pull DONE time 2us for resync */
    SENSCAN_RESYNC_LOW_TIME_4US     = 1,   /**< Sclk pull DONE time 4us for resync */
    SENSCAN_RESYNC_LOW_TIME_8US     = 2,   /**< Sclk pull DONE time 8us for resync */
    SENSCAN_RESYNC_LOW_TIME_16US    = 3,   /**< Sclk pull DONE time 16us for resync */
    SENSCAN_RESYNC_LOW_TIME_32US    = 4,   /**< Sclk pull DONE time 32us for resync */
    SENSCAN_RESYNC_LOW_TIME_64US    = 5,   /**< Sclk pull DONE time 64us for resync */
    SENSCAN_RESYNC_LOW_TIME_128US   = 6,   /**< Sclk pull DONE time 128us for resync */
    SENSCAN_RESYNC_LOW_TIME_256US   = 7,   /**< Sclk pull DONE time 256us for resync */
    SENSCAN_RESYNC_LOW_TIME_512US   = 8,   /**< Sclk pull DONE time 512us for resync */
    SENSCAN_RESYNC_LOW_TIME_1MS     = 9,   /**< Sclk pull DONE time 1ms for resync */
    SENSCAN_RESYNC_LOW_TIME_2MS     = 10,  /**< Sclk pull DONE time 2ms for resync */
    SENSCAN_RESYNC_LOW_TIME_4MS     = 11,  /**< Sclk pull DONE time 4ms for resync */
    SENSCAN_RESYNC_LOW_TIME_6MS     = 12,  /**< Sclk pull DONE time 6ms for resync */
    SENSCAN_RESYNC_LOW_TIME_8MS     = 13,  /**< Sclk pull DONE time 8ms for resync */
    SENSCAN_RESYNC_LOW_TIME_10MS    = 14,  /**< Sclk pull DONE time 10ms for resync */
    SENSCAN_RESYNC_LOW_TIME_12MS    = 15,  /**< Sclk pull DONE time 12ms for resync */
    SENSCAN_RESYNC_LOW_TIME_16MS    = 16,  /**< Sclk pull DONE time 16ms for resync */
    SENSCAN_RESYNC_LOW_TIME_24MS    = 17,  /**< Sclk pull DONE time 24ms for resync */
    SENSCAN_RESYNC_LOW_TIME_32MS    = 18,  /**< Sclk pull DONE time 32ms for resync */
} senscan_resync_low_time_t;
/**
 * @}
 */

/**
 * @defgroup senscan_control_t DRV_SENSCAN control type
 * @{
 */
typedef enum {
    SENSCAN_CONTROL_RESET               = 0,     /**< Reset SENSCAN */
    SENSCAN_CONTROL_CLK_DISABLE         = 1,     /**< Disable SENSCAN clock */
    SENSCAN_CONTROL_CLK_ENABLE          = 2,     /**< Enable SENSCAN clock */
    SENSCAN_CONTROL_SET_SCAN_FREQ       = 3,     /**< Set scan time */
    SENSCAN_CONTROL_CLEAR_DELTAXY_DATA  = 4,     /**< Clear deltax xy data */
    SENSCAN_CONTROL_WAKEUP_EN           = 5,     /**< Wakeup enable */
    SENSCAN_CONTROL_SCAN_EN             = 6,     /**< scan enable */
    SENSCAN_CONTROL_WAKEUP_DISABLE      = 7,     /**< Wakeup disenable */
    SENSCAN_CONTROL_SCAN_MODE_SEL       = 8,     /**< Select single mode or continuous mode */    
} senscan_control_t;
/**
 * @}
 */

/**
 * @defgroup senscan_spi_mode_t DRV_SENSCAN spi mode type
 * @{
 */
typedef enum {
    SENSCAN_SPI_MODE_4_WIRE         = 0,     /**< 4-wire spi */
    SENSCAN_SPI_MODE_2_WIRE         = 1,     /**< 2-wire spi */
} senscan_spi_mode_t;
/**
 * @}
 */

/**
 * @defgroup senscan_mode_t DRV_SENSCAN mode type
 * @{
 */
typedef enum {
    SENSCAN_MODE_SCAN         = 0,     /**< scan mode */
    SENSCAN_MODE_CONFIG       = 1,     /**< config mode */
} senscan_mode_t;
/**
 * @}
 */

/**
 * @brief DRV_SENSCAN configuration init stucture
 * @{
 */
typedef struct {
    union {
        uint8_t addr[7];
        struct {
            uint8_t idaddr;                          /**< SENSCAN id address */
            uint8_t id;                              /**< SENSCAN id */
            uint8_t moaddr;                          /**< SENSCAN motion address */
            uint8_t xaddr;                           /**< SENSCAN deltaX lower-bit data register address */
            uint8_t yaddr;                           /**< SENSCAN deltaY lower-bit data register address */
            uint8_t haddr1;                          /**< SENSCAN upper-bit coordinate data register address1 */
            uint8_t haddr2;                          /**< SENSCAN upper-bit coordinate data register address2 */
        };
    };
    uint8_t                    scan_freq;            /**< SENSCAN scan_freq, scan time = (scan_freq + 1)*0.25, unit is ms */
    senscan_resync_low_time_t  resync_low_time;      /**< SENSCAN sclk pull down time for resync, see @ref senscan_resync_low_time_t */
    senscan_resync_high_time_t resync_high_time;     /**< SENSCAN sclk pull up time for resync, see @ref senscan_resync_high_time_t */
    uint8_t                    t_srad : 4;           /**< SENSCAN from rising SCLK for last bit of the address bytes to falling SCLK for first bit of data being read,Tsrad=(t_srad+1)*0.25us */
    uint8_t                    t_srr : 4;            /**< SENSCAN from rising SCLK for last bit of the first data byte to falling SCLK for first bit of data if the next command,Tsrr=(t_srr+5)*0.25us */
    uint8_t                    t_sclk_ncs : 4;       /**< SENSCAN last SCLK rising edge to NSC rising edge,for valid MISO data transfer,Tsclk-ncs=(t_sclk_ncs+1)*0.25us */
    uint8_t                    t_ncs_sclk : 4;       /**< SENSCAN last NCS falling edge to first SCLK rising edge, Tncs-sclk=(t_ncs_sclk+1)*0.25us */
    senscan_scan_mode_t        mode : 1;             /**< SENSCAN mode type, see @ref senscan_scan_mode_t */
    senscan_data_format_t      data_format : 2;      /**< SENSCAN data format type, see @ref senscan_data_format_t */
    senscan_deltaxy_rev_t      deltaxy_rev : 1;      /**< SENSCAN deltaXY revert type, see @ref senscan_deltaxy_rev_t */
    senscan_spi_mode_t         spi_mode : 1;         /**< SENSCAN spi mode type, see @ref senscan_spi_mode_t */
} senscan_config_t;
/**
 * @}
 */


/*******************************************************************************
 * EXTERN FUNCTIONS
 */
/**
 *******************************************************************************
 * @brief Initialize the SENSCAN with parameters in senscan_config_t
 *
 * @param config            The configuration structure pointer, see @ref senscan_config_t
 *
 *******************************************************************************
 */
extern void drv_senscan_init(void);

/**
 *******************************************************************************
 * @brief Sensor scanning by polling mode
 *
 * @param om_senscan        The SENSCAN device address
 * @param x_data            The x_deltax data to be read from sensor device
 * @param y_data            The y_deltax data to be read from sensor device
 *
 * @return                  deltaXY data address
 *******************************************************************************
 */
extern om_error_t drv_senscan_start(OM_SENSCAN_Type *om_senscan, uint32_t *x_data, uint32_t *y_data);

/**
 *******************************************************************************
 * @brief Sensor scanning by interrupt mode
 *
 * @param om_senscan        The SENSCAN device address
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern om_error_t drv_senscan_start_int(OM_SENSCAN_Type *om_senscan);

/**
 *******************************************************************************
 * @brief Stop sensor scanning
 *
 * @param om_senscan        The SENSCAN device address
 *
 * @return                  status, see@ref om_error_t
 *******************************************************************************
 */
extern void drv_senscan_stop(void);
extern void drv_senscan_begin(void);

/**
 *******************************************************************************
 * @brief sensor write
 *
 * @param om_senscan        The SENSCAN device address
 * @param sensor_addr       The sensor device address
 * @param sensor_data       The data to be write to sensor device
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_senscan_write(uint8_t      sensor_addr,
                              uint8_t      sensor_data);

/**
 *******************************************************************************
 * @brief sensor read
 *
 * @param om_senscan        The SENSCAN device address
 * @param sensor_addr       The sensor device address
 *
 * @return                  The data to be read from sensor device
 *******************************************************************************
 */
extern uint8_t drv_senscan_read(uint8_t sensor_addr);

/**
 *******************************************************************************
 * @brief 2wire spi actively initiate sync
 *
 * @param om_senscan        The SENSCAN device address
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_senscan_2wire_resync(void);

/**
 *******************************************************************************
 * @brief Senscan mode select
 *
 * @param om_senscan        The SENSCAN device address
 * @param mode              The SENSCAN mode, see @ref senscan_mode_t
 *
 * @return                  None
 *******************************************************************************
 */
extern void drv_senscan_mode_select(OM_SENSCAN_Type *om_senscan, senscan_mode_t mode);

/**
 *******************************************************************************
 * @brief Control SENSCAN interface
 *
 * @param om_senscan      The SENSCAN device address
 * @param control        The control operation type, see @ref senscan_control_t
 * @param argu           The correspondence between the argu parameter and control parameter
 *                       described as followed:
 *                       - SENSCAN_CONTROL_CLK_DISABLE           Disable SENSCAN clock,argu=NULL
 *                       - SENSCAN_CONTROL_CLK_ENABLE            Enable SENSCAN clock,argu=NULL
 *                       - SENSCAN_CONTROL_RESET                 Reset SENSCAN, argu=NULL
 *
 * @return               status, see@ref om_error_t
 *******************************************************************************
 */
extern void *drv_senscan_control(OM_SENSCAN_Type *om_senscan, senscan_control_t control, void *argu);

#if (RTE_SENSCAN_REGISTER_CALLBACK)
/**
 *******************************************************************************
 * @brief Register interrupt service routine callback for specified SENSCAN device interrupt
 *
 * @param om_senscan        The SENSCAN device address
 * @param isr_cb            The event callback function, see @ref drv_isr_callback_t
 *
 * @return None
 *******************************************************************************
 */
extern void drv_senscan_register_isr_callback(OM_SENSCAN_Type *om_senscan, drv_isr_callback_t isr_cb);
#endif /* (RTE_SENSCAN_REGISTER_CALLBACK) */

#ifdef __cplusplus
}
#endif
#endif  /* (RTE_SENSCAN) */

#endif  /* __DRV_SENSCAN_H */

/** @} */
