#include "PCA9685.h"

#include <cmath>

char ADDR;

void PCA9685_Init(char addr)
{
    ADDR = addr;
    DEV_I2C_WriteByte(ADDR, MODE1, 0x00);
}

void PCA9685_SetPWMFreq(UWORD freq)
{
    freq *= 0.9;
    double prescaleval = 25000000.0;
    prescaleval /= 4096.0;
    prescaleval /= freq;
    prescaleval -= 1;
    UBYTE prescale = round(prescaleval + 0.5);

    UBYTE oldmode = DEV_I2C_ReadByte(ADDR, MODE1);
    UBYTE newmode = (oldmode & 0x7F) | 0x10;

    DEV_I2C_WriteByte(ADDR, MODE1, newmode);
    DEV_I2C_WriteByte(ADDR, PRESCALE, prescale);
    DEV_I2C_WriteByte(ADDR, MODE1, oldmode);
    DEV_Delay_ms(5);
    DEV_I2C_WriteByte(ADDR, MODE1, oldmode | 0x80);
}

void PCA9685_SetPwmDutyCycle(UBYTE channel, UWORD pulse)
{
    DEV_I2C_WriteByte(ADDR, LED0_ON_L + 4*channel, 0 & 0xFF);
    DEV_I2C_WriteByte(ADDR, LED0_ON_H + 4*channel, 0 >> 8);
    DEV_I2C_WriteByte(ADDR, LED0_OFF_L + 4*channel, (pulse * (4096/100) -1) & 0xFF);
    DEV_I2C_WriteByte(ADDR, LED0_OFF_H + 4*channel, (pulse * (4096/100) -1) >> 8);
}

void PCA9685_SetLevel(UBYTE channel, UWORD value)
{
    if(value == 1){
        DEV_I2C_WriteByte(ADDR, LED0_ON_L + 4*channel, 0 & 0xFF);
        DEV_I2C_WriteByte(ADDR, LED0_ON_H + 4*channel, 0 >> 8);
        DEV_I2C_WriteByte(ADDR, LED0_OFF_L + 4*channel, 4095 & 0xFF);
        DEV_I2C_WriteByte(ADDR, LED0_OFF_H + 4*channel, 4095 >> 8);
    }
    else{
        DEV_I2C_WriteByte(ADDR, LED0_ON_L + 4*channel, 0 & 0xFF);
        DEV_I2C_WriteByte(ADDR, LED0_ON_H + 4*channel, 0 >> 8);
        DEV_I2C_WriteByte(ADDR, LED0_OFF_L + 4*channel, 0 & 0xFF);
        DEV_I2C_WriteByte(ADDR, LED0_OFF_H + 4*channel, 0 >> 8);
    }
}
