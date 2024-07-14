
#ifndef __CS5532_H__
#define __CS5532_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "definitions.h"


typedef enum calibrate_type_t { 
    CS5532_SELF_OFFSET = (uint8_t)1, 
    CS5532_SELF_GAIN = (uint8_t)2,
    CS5532_SYSTEM_OFFSET = (uint8_t)3, 
    CS5532_SYSTEM_GAIN = (uint8_t)4
} calibrate_type_t;


#define CS5532_SYNC1      0xFF  //Part of the serial port re-initialization sequence.
#define CS5532_SYNC0      0xFE  //End of the serial port re-initialization sequence.

#define CS5532_NULL       0x00  //This command is used to clear a port flag and keep the converter in the continuous conversion mode.

/*
//Command Register (CS5532_COMM_REG)
#define CS5532_COMM_C               (1 << 7)              //D7 Command Bit, C
#define CS5532_COMM_ARA             (1 << 6)              //D6 Access Registers as Arrays, ARA
#define CS5532_COMM_CS              (((x) & 0x3) << 4)    //D5-D4 Channel Select Bits,CS1-CS0
#define CS5532_COMM_READ            (1 << 3)              //D3 Read/Write, R/W
#define CS5532_COMM_WRITE           (0 << 3)
#define CS5532_COMM_RSB             (((x) & 0x7) << 0)    //D2-D0 Register Select Bit,RSB3-RSB0
*/

//alıntı
#define CS5532_READ_DATA_TIMEOUT 2000000    //4.9152 MHz crystal takes 20ms to start






// used with  CS5532_WriteRegister(CS5532_CMD_WRITE_CH_SETUP_REG1, 0x3200000);
//Command Register Descriptions
/*READ/WRITE ALL OFFSET CALIBRATION REGISTERS*/
#define CS5532_CMD_READ_ALL_OFFSET_CAL            0x49
#define CS5532_CMD_WRITE_ALL_OFFSET_CAL           0x41

/*READ/WRITE ALL GAIN CALIBRATION REGISTERS*/
#define CS5532_CMD_READ_ALL_GAIN_CAL              0x4A
#define CS5532_CMD_WRITE_ALL_GAIN_CAL             0x42

/*READ/WRITE ALL CHANNEL-SETUP REGISTERS*/
#define CS5532_CMD_READ_ALL_CH_SETUP              0x4D
#define CS5532_CMD_WRITE_ALL_CH_SETUP             0x45

/*READ/WRITE OFFSET REGISTER*/
#define CS5532_CMD_READ_OFFSET_REG1               0x09
#define CS5532_CMD_WRITE_OFFSET_REG1              0x01
#define CS5532_CMD_READ_OFFSET_REG2               0x19
#define CS5532_CMD_WRITE_OFFSET_REG2              0x11

/*READ/WRITE GAIN REGISTER*/
#define CS5532_CMD_READ_GAIN_REG1                0x0A
#define CS5532_CMD_WRITE_GAIN_REG1               0x02
#define CS5532_CMD_READ_GAIN_REG2                0x1A
#define CS5532_CMD_WRITE_GAIN_REG2               0x12

/*READ/WRITE CHANNEL-SETUP REGISTER*/
#define CS5532_CMD_READ_CH_SETUP_REG1            0x0D
#define CS5532_CMD_WRITE_CH_SETUP_REG1           0x05
#define CS5532_CMD_READ_CH_SETUP_REG2            0x1D
#define CS5532_CMD_WRITE_CH_SETUP_REG2           0x15
#define CS5532_CMD_READ_CH_SETUP_REG3            0x2D
#define CS5532_CMD_WRITE_CH_SETUP_REG3           0x25
#define CS5532_CMD_READ_CH_SETUP_REG4            0x3D
#define CS5532_CMD_WRITE_CH_SETUP_REG4           0x35

/*READ/WRITE CONFIGURATION REGISTER*/
#define CS5532_CMD_READ_CONFIG_REG               0x0B
#define CS5532_CMD_WRITE_CONFIG_REG              0x03






/*PERFORM CONVERSION, used with CS5532_WriteCommand() */
//Perform a single conversion.
#define CS5532_CMD_SINGLE_CONV_CH_SETUP1          0x80
#define CS5532_CMD_SINGLE_CONV_CH_SETUP2          0x88
#define CS5532_CMD_SINGLE_CONV_CH_SETUP3          0x90
#define CS5532_CMD_SINGLE_CONV_CH_SETUP4          0x98
#define CS5532_CMD_SINGLE_CONV_CH_SETUP5          0xA0
#define CS5532_CMD_SINGLE_CONV_CH_SETUP6          0xA8
#define CS5532_CMD_SINGLE_CONV_CH_SETUP7          0xB0
#define CS5532_CMD_SINGLE_CONV_CH_SETUP8          0xB8

//Perform continuous conversions.
#define CS5532_CMD_CONTINUOUS_CONV_CH_SETUP1      0xC0
#define CS5532_CMD_CONTINUOUS_CONV_CH_SETUP2      0xC8
#define CS5532_CMD_CONTINUOUS_CONV_CH_SETUP3      0xD0
#define CS5532_CMD_CONTINUOUS_CONV_CH_SETUP4      0xD8
#define CS5532_CMD_CONTINUOUS_CONV_CH_SETUP5      0xE0
#define CS5532_CMD_CONTINUOUS_CONV_CH_SETUP6      0xE8
#define CS5532_CMD_CONTINUOUS_CONV_CH_SETUP7      0xF0
#define CS5532_CMD_CONTINUOUS_CONV_CH_SETUP8      0xF8





/*PERFORM CALIBRATION*/
//001 Self-Offset Calibration
#define CS5532_CMD_SELF_OFFSET_CALIB_SETUP1       0x81
#define CS5532_CMD_SELF_OFFSET_CALIB_SETUP2       0x89
#define CS5532_CMD_SELF_OFFSET_CALIB_SETUP3       0x91
#define CS5532_CMD_SELF_OFFSET_CALIB_SETUP4       0x99
#define CS5532_CMD_SELF_OFFSET_CALIB_SETUP5       0xA1
#define CS5532_CMD_SELF_OFFSET_CALIB_SETUP6       0xA9
#define CS5532_CMD_SELF_OFFSET_CALIB_SETUP7       0xB1
#define CS5532_CMD_SELF_OFFSET_CALIB_SETUP8       0xB9

//010 Self-Gain Calibration
#define CS5532_CMD_SELF_GAIN_CALIB_SETUP1         0x82
#define CS5532_CMD_SELF_GAIN_CALIB_SETUP2         0x8A
#define CS5532_CMD_SELF_GAIN_CALIB_SETUP3         0x92
#define CS5532_CMD_SELF_GAIN_CALIB_SETUP4         0x9A
#define CS5532_CMD_SELF_GAIN_CALIB_SETUP5         0xA2
#define CS5532_CMD_SELF_GAIN_CALIB_SETUP6         0xAA
#define CS5532_CMD_SELF_GAIN_CALIB_SETUP7         0xB2
#define CS5532_CMD_SELF_GAIN_CALIB_SETUP8         0xBA

//101 System-Offset Calibration
#define CS5532_CMD_SYS_OFFSET_CALIB_SETUP1        0x85
#define CS5532_CMD_SYS_OFFSET_CALIB_SETUP2        0x8D
#define CS5532_CMD_SYS_OFFSET_CALIB_SETUP3        0x95
#define CS5532_CMD_SYS_OFFSET_CALIB_SETUP4        0x9D
#define CS5532_CMD_SYS_OFFSET_CALIB_SETUP5        0xA5
#define CS5532_CMD_SYS_OFFSET_CALIB_SETUP6        0xAD
#define CS5532_CMD_SYS_OFFSET_CALIB_SETUP7        0xB5
#define CS5532_CMD_SYS_OFFSET_CALIB_SETUP8        0xBD

//110 System-Gain Calibration
#define CS5532_CMD_SYS_GAIN_CALIB_SETUP1          0x86
#define CS5532_CMD_SYS_GAIN_CALIB_SETUP2          0x8E
#define CS5532_CMD_SYS_GAIN_CALIB_SETUP3          0x96
#define CS5532_CMD_SYS_GAIN_CALIB_SETUP4          0x9E
#define CS5532_CMD_SYS_GAIN_CALIB_SETUP5          0xA6
#define CS5532_CMD_SYS_GAIN_CALIB_SETUP6          0xAE
#define CS5532_CMD_SYS_GAIN_CALIB_SETUP7          0xB6
#define CS5532_CMD_SYS_GAIN_CALIB_SETUP8          0xBE




// example usage: CS5532_WriteRegister(CS5532_CMD_WRITE_CONFIG_REG, CS5532_RS)
//2.3.9. Configuration Register Descriptions
#define CS5532_PSS        ((uint32_t)(1U << 31U))     //Power Save Select
#define CS5532_PDW        ((uint32_t)(1U << 30U))     //Power Down Mode
#define CS5532_RS         ((uint32_t)(1U << 29U))     //Reset System
#define CS5532_RV         ((uint32_t)(1U << 28U))     //Reset Valid
#define CS5532_IS         ((uint32_t)(1U << 27U))     //Input Short
#define CS5532_GB         ((uint32_t)(1U << 26U))     //Guard Signal Bit
#define CS5532_VRS        ((uint32_t)(1U << 25U))     //Voltage Reference Select
#define CS5532_OLS        ((uint32_t)(1U << 22U))     //Output Latch Select
#define CS5532_OGS        ((uint32_t)(1U << 20U))     //Offset and Gain Select
#define CS5532_FRS        ((uint32_t)(1U << 19U))     //Filter Rate Select




// example usage: CS5532_WriteRegister(CS5532_CMD_WRITE_CH_SETUP_REG1, 0x3200000);
//2.4.1. Channel-Setup Register
//Channel Select Bits
#define CS5532_CS0        ((uint16_t)(0U << 14U))
#define CS5532_CS1        ((uint16_t)(1U << 14U))

//Gain Bits
#define CS5532_GAIN_1     ((uint16_t)(0U << 11U))
#define CS5532_GAIN_2     ((uint16_t)(1U << 11U))
#define CS5532_GAIN_4     ((uint16_t)(2U << 11U))
#define CS5532_GAIN_8     ((uint16_t)(3U << 11U))
#define CS5532_GAIN_16    ((uint16_t)(4U << 11U))
#define CS5532_GAIN_32    ((uint16_t)(5U << 11U))
#define CS5532_GAIN_64    ((uint16_t)(6U << 11U))

//Word Rate when FRS=0
#define CS5532_WR_FRS0_120SPS    ((uint16_t)(0x0U << 7U))
#define CS5532_WR_FRS0_60SPS     ((uint16_t)(0x1U << 7U))
#define CS5532_WR_FRS0_30SPS     ((uint16_t)(0x2U << 7U))
#define CS5532_WR_FRS0_15P5SPS   ((uint16_t)(0x3U << 7U))
#define CS5532_WR_FRS0_7P5SPS    ((uint16_t)(0x4U << 7U))
#define CS5532_WR_FRS0_3840SPS   ((uint16_t)(0x8U << 7U))
#define CS5532_WR_FRS0_1920SPS   ((uint16_t)(0x9U << 7U))
#define CS5532_WR_FRS0_960SPS    ((uint16_t)(0xAU << 7U))
#define CS5532_WR_FRS0_480SPS    ((uint16_t)(0xBU << 7U))
#define CS5532_WR_FRS0_240SPS    ((uint16_t)(0xCU << 7U))

//Word Rate when FRS=1
#define CS5532_WR_FRS1_100SPS    ((uint16_t)(0x0U << 7U))
#define CS5532_WR_FRS1_50SPS     ((uint16_t)(0x1U << 7U))
#define CS5532_WR_FRS1_25SPS     ((uint16_t)(0x2U << 7U))
#define CS5532_WR_FRS1_12P5SPS   ((uint16_t)(0x3U << 7U))
#define CS5532_WR_FRS1_6P25SPS   ((uint16_t)(0x4U << 7U))
#define CS5532_WR_FRS1_3200SPS   ((uint16_t)(0x8U << 7U))
#define CS5532_WR_FRS1_1600SPS   ((uint16_t)(0x9U << 7U))
#define CS5532_WR_FRS1_800SPS    ((uint16_t)(0xAU << 7U))
#define CS5532_WR_FRS1_400SPS    ((uint16_t)(0xBU << 7U))
#define CS5532_WR_FRS1_200SPS    ((uint16_t)(0xCU << 7U))

//Unipolar / Bipolar
#define CS5532_UNIPOLAR          ((uint16_t)(1U << 6U))
#define CS5532_BIPOLAR           ((uint16_t)(0U << 6U))

//Output Latch Bits
#define CS5532_OL0               ((uint16_t)(0U << 4U))
#define CS5532_OL1               ((uint16_t)(1U << 4U))
#define CS5532_OL2               ((uint16_t)(2U << 4U))
#define CS5532_OL3               ((uint16_t)(3U << 4U))

//Delay Time Bit
#define CS5532_DT0               ((uint16_t)(0U << 3U))
#define CS5532_DT1               ((uint16_t)(1U << 3U))

//Open Circuit Detect Bit
#define CS5532_OCD0              ((uint16_t)(0U << 2U))
#define CS5532_OCD1              ((uint16_t)(1U << 2U))

//Offset / Gain Register Pointer Bits
#define CS5532_OG0               ((uint16_t)(0U))
#define CS5532_OG1               ((uint16_t)(1U))






//alıntı
#define CMD_STOP_CONT_CONV 0xFF

#define TIMEOUTERR 0xFF
#define SUCCESSFUL 0x0
#define CAL_TIMEOUT_LIMIT 4000

#define CS5532_RESET_TIME 1200000
#define CS5532_WASTE_TIME 90000000

unsigned long CS5532_Init(void);
void CS5532_Example(void);
static inline void CS5532_WriteRegister(uint8_t reg, uint32_t dat);
static inline uint32_t CS5532_ReadRegister(uint8_t reg);
int32_t CS5532_Get_Data(uint8_t channel);

void CS5532_delay(uint32_t  delay);


#endif
