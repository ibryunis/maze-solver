#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"

#include "RobotCar.h"

int main()
{
    RobotCar car;
    car.Run();
    return 0;
}
