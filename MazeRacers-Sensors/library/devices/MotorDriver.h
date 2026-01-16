#ifndef __MOTORDRIVER_H_
#define __MOTORDRIVER_H_

#include "DEV_Config.h"
#include "PCA9685.h"

#define MOTORA       0
#define MOTORB       1
#define MOTORC       2
#define MOTORD       3

typedef enum{
    FORWARD = 0,
    BACKWARD ,
} DIR;

void Motor_Init(void);
void Motor_Run(UBYTE motor, DIR dir, UWORD speed);
void Motor_Stop(UBYTE motor);
void Motor_Test(void);

#endif