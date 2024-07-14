
#include "CS5532.h"
//#include "plib_spi3_master.h"
#include <math.h>

// <editor-fold defaultstate="collapsed" desc="SPI3 HW Functions">

static inline void SPI3_Writing_Byte(uint8_t data)
{
    SPI3CONbits.MODE16 = 0;
    SPI3CONbits.MODE32 = 0;

    SPI3_WriteRead(&data, 1, NULL, 0);
}

static inline void SPI3_Writing_Word(uint16_t data)
{
    SPI3CONbits.MODE16 = 1;
    SPI3CONbits.MODE32 = 0;

    SPI3_WriteRead(&data, 2, NULL, 0);
}

static inline void SPI3_Writing_Long(uint32_t data)
{
    SPI3CONbits.MODE16 = 0;
    SPI3CONbits.MODE32 = 1;

    SPI3_WriteRead(&data, 4, NULL, 0);
}

static inline uint8_t SPI3_Reading_Byte(void)
{
    SPI3CONbits.MODE16 = 0;
    SPI3CONbits.MODE32 = 0;

    uint8_t RxData = 0;

    SPI3_WriteRead(NULL, 0, &RxData, 1);

    return RxData;
}

static inline uint32_t SPI3_Reading_Long(void)
{
    SPI3CONbits.MODE16 = 0;
    SPI3CONbits.MODE32 = 1;

    uint32_t RxData = 0;

    SPI3_WriteRead(NULL, 0, &RxData, 4);

    return RxData;
}
// </editor-fold>

static inline void CS5532_WriteRegister(uint8_t reg, uint32_t dat)
{
    GPIO_RB10_Clear();
    SPI3_Writing_Byte(reg);
    SPI3_Writing_Long(dat);
    GPIO_RB10_Set();
}

static inline uint32_t CS5532_ReadRegister(uint8_t reg)
{
    uint32_t ret;

    GPIO_RB10_Clear();
    SPI3_Writing_Byte(reg);
    ret = SPI3_Reading_Long();
    GPIO_RB10_Set();

    return ret;
}

static inline void CS5532_WriteCommand(uint8_t cmd)
{
    GPIO_RB10_Clear();
    SPI3_Writing_Byte(cmd);
    GPIO_RB10_Set();
}

unsigned long CS5532_Init(void)
{
    for (uint8_t i = 0; i < 15; i++) {
        CS5532_WriteCommand(CS5532_SYNC1);
    }
    CS5532_WriteCommand(CS5532_SYNC0);
    CS5532_delay(50);
    
    // CS5532 Reset
    CS5532_WriteRegister(CS5532_CMD_WRITE_CONFIG_REG, CS5532_RS);
    CS5532_delay(10);
    // CS5532 Reset Done
    unsigned long RV = CS5532_ReadRegister(CS5532_CMD_READ_CONFIG_REG);
    unsigned char RV_bit = RV && 0x10000000;
    if (RV_bit == 1) {
        SYS_CONSOLE_PRINT("Reset is Done\r\n");
        CS5532_WriteRegister(CS5532_CMD_WRITE_CONFIG_REG, CS5532_NULL);
    }
    CS5532_delay(10);
    
    // Read initial state
//    CS5532_ReadRegister(CS5532_CMD_READ_CONFIG_REG);
//    CS5532_ReadRegister(CS5532_CMD_READ_CONFIG_REG);
//    CS5532_ReadRegister(CS5532_CMD_READ_OFFSET_REG1);
//    CS5532_ReadRegister(CS5532_CMD_READ_OFFSET_REG2);
//    CS5532_ReadRegister(CS5532_CMD_READ_GAIN_REG1);
//    CS5532_ReadRegister(CS5532_CMD_READ_GAIN_REG2);
//    CS5532_ReadRegister(CS5532_CMD_READ_CH_SETUP_REG1);
//    CS5532_ReadRegister(CS5532_CMD_READ_CH_SETUP_REG2);
//    CS5532_ReadRegister(CS5532_CMD_READ_CH_SETUP_REG3);
//    CS5532_ReadRegister(CS5532_CMD_READ_CH_SETUP_REG4);
   
    CS5532_delay(10);
    
    // Configure Gain 1
    uint32_t ReadGainReg = 0;
    CS5532_WriteRegister(CS5532_CMD_WRITE_GAIN_REG1, 0x01000000);
    ReadGainReg = CS5532_ReadRegister(CS5532_CMD_READ_GAIN_REG1);
    SYS_CONSOLE_PRINT("config Gain1: 0x%X\r\n", ReadGainReg);
    
    // Configure Gain 2
    CS5532_WriteRegister(CS5532_CMD_WRITE_GAIN_REG2, 0x01000000);
    ReadGainReg = CS5532_ReadRegister(CS5532_CMD_READ_GAIN_REG2);
    SYS_CONSOLE_PRINT("config Gain2: 0x%X\r\n", ReadGainReg);

    // Configure Channel 1
    unsigned long bip1 = CS5532_ReadRegister(CS5532_CMD_READ_CH_SETUP_REG1);
    SYS_CONSOLE_PRINT("CH_SETUP_REG1: 0x%X\r\n", bip1);
    CS5532_WriteRegister(CS5532_CMD_WRITE_CH_SETUP_REG1, (uint32_t) (CS5532_CS0 | CS5532_WR_FRS0_120SPS | CS5532_UNIPOLAR) << 16U); // channel setup 1
    bip1 = CS5532_ReadRegister(CS5532_CMD_READ_CH_SETUP_REG1);
    SYS_CONSOLE_PRINT("CH_SETUP_REG1_new: 0x%X\r\n", bip1);
    
    // Configure Channel 2
    unsigned long bip2 = CS5532_ReadRegister(CS5532_CMD_READ_CH_SETUP_REG2);
    SYS_CONSOLE_PRINT("CH_SETUP_REG2: 0x%X\r\n", bip2);
    CS5532_WriteRegister(CS5532_CMD_WRITE_CH_SETUP_REG2, (uint32_t) (CS5532_CS1 | CS5532_WR_FRS0_120SPS | CS5532_UNIPOLAR) << 16U); // channel setup 3
    bip2 = CS5532_ReadRegister(CS5532_CMD_READ_CH_SETUP_REG2);
    SYS_CONSOLE_PRINT("CH_SETUP_REG2_new: 0x%X\r\n", bip2);
        
//    // VRS=0 and FRS=1
//    CS5532_WriteRegister(CS5532_CMD_WRITE_CONFIG_REG, CS5532_FRS);
//    unsigned long vref = CS5532_ReadRegister(CS5532_CMD_READ_CONFIG_REG);
//    SYS_CONSOLE_PRINT("config setup: 0x%X\r\n", vref);
    
//    // Configure Offset 1
//    uint32_t ReadOffsetReg = 0;
//    CS5532_WriteRegister(CS5532_CMD_WRITE_OFFSET_REG1, 0x00000000); // 0XFFFD0000
//    CS5532_delay(100);
//    ReadOffsetReg = CS5532_ReadRegister(CS5532_CMD_READ_OFFSET_REG1);
//    SYS_CONSOLE_PRINT("config Offset1: 0x%X\r\n", ReadOffsetReg);
//    
//    // Configure Offset 2
//    CS5532_WriteRegister(CS5532_CMD_WRITE_OFFSET_REG2, 0x00000000); // 0XFFFD0000
//    CS5532_delay(100);
//    ReadOffsetReg = CS5532_ReadRegister(CS5532_CMD_READ_OFFSET_REG2);
//    SYS_CONSOLE_PRINT("config Offset2: 0x%X\r\n", ReadOffsetReg);
    
    CS5532_delay(10);
    
//    CS5532_WriteCommand(CS5532_CMD_SINGLE_CONV_CH_SETUP1);
//    CS5532_WriteCommand(CS5532_CMD_SINGLE_CONV_CH_SETUP3);
    
//    CS5532_WriteCommand(CS5532_CMD_CONTINUOUS_CONV_CH_SETUP1);
//    CS5532_WriteCommand(CS5532_CMD_CONTINUOUS_CONV_CH_SETUP3);
    
//    CS5532_delay(10);
}

int32_t CS5532_Get_Data(uint8_t channel)
{
    uint32_t Buffer = 0;
    uint8_t ControlByte = 0;
    int32_t DataByte = 0;
    
    GPIO_RB10_Clear();
    
    if (channel == 1) {
        SPI3_Writing_Byte(CS5532_CMD_SINGLE_CONV_CH_SETUP1);
    }
    else if (channel == 2) {
        SPI3_Writing_Byte(CS5532_CMD_SINGLE_CONV_CH_SETUP3);
    }
    else {
        GPIO_RB10_Set();
        return -1; // Invalid channel
    }
    
    //for (uint32_t waste_time = 10000; waste_time > 0; waste_time--);
    CS5532_delay(140);
    
    SPI3_Writing_Byte(CS5532_NULL); //The first 8 SCLKs are used to clear the SDO flag  
    Buffer = SPI3_Reading_Long();
    
    GPIO_RB10_Set();
    
    ControlByte = (uint8_t) (Buffer & 0xFF);
    
    DataByte = (int32_t) (Buffer >> 8U);
    
    if (ControlByte & 0x04) // Check for overflow
    {
        return -INT32_MAX; // Overflow error
    }

    return DataByte;
}

uint8_t CS5532_Calibrate(calibrate_type_t calibrate_type, int cfg_reg, int setup_reg)
{
    // according fig.3 p.12 for IN+, IN-

    uint32_t calibrate_result;
    
    int i;
    cfg_reg = (int) ((calibrate_type % 2 == 1) ? (cfg_reg | CS5532_IS) : (cfg_reg));
    uint8_t cmd, read_reg;

    switch (calibrate_type)
    {
        case CS5532_SELF_OFFSET:
            cmd = CS5532_CMD_SELF_OFFSET_CALIB_SETUP1;
            read_reg = CS5532_CMD_READ_OFFSET_REG1;
            break;
        case CS5532_SELF_GAIN:
            cmd = CS5532_CMD_SELF_GAIN_CALIB_SETUP1;
            read_reg = CS5532_CMD_READ_GAIN_REG1;
            break;
        case CS5532_SYSTEM_OFFSET:
            cmd = CS5532_CMD_SYS_OFFSET_CALIB_SETUP1;
            read_reg = CS5532_CMD_READ_OFFSET_REG1;
            break;
        case CS5532_SYSTEM_GAIN:
            cmd = CS5532_CMD_SYS_GAIN_CALIB_SETUP1;
            read_reg = CS5532_CMD_READ_GAIN_REG1;
            break;
    }

    CS5532_WriteRegister(CS5532_CMD_WRITE_CH_SETUP_REG1, setup_reg);
    CS5532_WriteRegister(CS5532_CMD_WRITE_CONFIG_REG, cfg_reg);
    CS5532_WriteCommand(cmd);

    for (uint32_t waste_time = CS5532_WASTE_TIME; waste_time > 0; waste_time--);

    calibrate_result = CS5532_ReadRegister(read_reg);

    printf("The calibration result is: %X\r\n", calibrate_result);

    return 1;
}

void CS5532_Example(void)
{
    unsigned char tempbuff[4] = {0x0, 0x0, 0x0, 0x0};
    float data;
    unsigned char OF;
    unsigned long res = 0;

    *(uint32_t *) tempbuff = CS5532_ReadRegister(CS5532_NULL); //The first 8 SCLKs are used to clear the SDO flag  

    //    SYS_CONSOLE_PRINT("rawdata:");
    //    SYS_CONSOLE_PRINT("TOP:");
    //    SYS_CONSOLE_PRINT(tempbuff[0],BIN);
    //    SYS_CONSOLE_PRINT("   MSB:");
    //    SYS_CONSOLE_PRINT(tempbuff[1],BIN);
    //    SYS_CONSOLE_PRINT("   MDL:");
    //    SYS_CONSOLE_PRINT(tempbuff[2],BIN);
    //    SYS_CONSOLE_PRINT("   LSB:");
    //    SYS_CONSOLE_PRINT(tempbuff[3],BIN);
    //    delay(1000);

    OF = tempbuff[3] & 0x04;

    if (OF == 0x4) {
        SYS_CONSOLE_PRINT("error");
        CS5532_delay(1000);
    }
    else {
        res = tempbuff[0];
        res = (res << 8) + tempbuff[1];
        res = (res << 8) + tempbuff[2];
        res = 0xFFFFFF - res;
        res = res + 1;
        //        SYS_CONSOLE_PRINT("CH0:  %d\r\n", res);
        //    SYS_CONSOLE_PRINT("rawdata:");
        //    SYS_CONSOLE_PRINT(tempbuff[0],BIN);
        //    SYS_CONSOLE_PRINT("  ");
        //    SYS_CONSOLE_PRINT(tempbuff[1],BIN);
        //    SYS_CONSOLE_PRINT("  ");
        //    SYS_CONSOLE_PRINT(tempbuff[2],BIN);
        CS5532_delay(1000);
    }
}

void CS5532_delay(uint32_t delay)
{
    SYS_TIME_HANDLE tmrHandle = SYS_TIME_HANDLE_INVALID;
    SYS_TIME_DelayMS(delay, &tmrHandle);
    while (true != SYS_TIME_DelayIsComplete(tmrHandle)) {
        continue;
    }
}

