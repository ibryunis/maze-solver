#ifndef _ROBOTCAR_H_
#define _ROBOTCAR_H_

#include <stdio.h>
#include "MotorDriver.h"
#include "pico/stdlib.h"

// sensors ultrasonic pins
#define TRIG_PIN 2
#define ECHO_PIN 3

class RobotCar
{
public:
    RobotCar();
    ~RobotCar();
    void Run();

private:
    void MoveForward(int speed);
    void MoveBackward(int speed);
    void StopMotors();

    void Turn90Right(int speed);
    void Turn90Left(int speed);
    void Turn180Right(int speed);
    void Turn180Left(int speed);

    // sensor
    float ReadDistance();

    // right
    bool turn_right_next_ = true;

    // cfgs
    static constexpr int   MAX_SPEED   = 50;
    static constexpr float OBSTACLE_CM = 15.0f;
    static constexpr int   MS_PER_DEG  = 7;
};

#endif // _ROBOTCAR_H_