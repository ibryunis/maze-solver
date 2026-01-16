#include "MotorDriver.h"

int MotorPin[4][3] = {{0,1,2},{3,4,5},{6,7,8},{9,10,11}};
int MotorDir[2][2] = {{0,1}, {1,0}};

void Motor_Init(void)
{
    PCA9685_Init(0x40);
    PCA9685_SetPWMFreq(100);
}

void Motor_Run(UBYTE motor, DIR dir, UWORD speed)
{
    PCA9685_SetPwmDutyCycle(MotorPin[motor][0], speed);
    PCA9685_SetLevel(MotorPin[motor][1], MotorDir[dir][0]);
    PCA9685_SetLevel(MotorPin[motor][2], MotorDir[dir][1]);
}

void Motor_Stop(UBYTE motor)
{
    PCA9685_SetPwmDutyCycle(MotorPin[motor][0], 0);
}

void Motor_Test(void)
{
    if(DEV_Module_Init()!=0){
        DEV_Delay_ms(3000);
    }

    Motor_Init();
    Motor_Run(MOTORA, FORWARD, 100);
    Motor_Run(MOTORB, FORWARD, 100);
    Motor_Run(MOTORC, FORWARD, 100);
    Motor_Run(MOTORD, FORWARD, 100);
}
