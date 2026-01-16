// RobotCar.cpp
#include "RobotCar.h"
#include "DEV_Config.h"

RobotCar::RobotCar() {
    // initialize
    if (DEV_Module_Init() != 0) {
        DEV_Delay_ms(1000);
        DEV_Module_Init();
    }
    Motor_Init();

    // pins for sensors
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_put(TRIG_PIN, 0);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
    gpio_pull_down(ECHO_PIN);
}

RobotCar::~RobotCar() {
    StopMotors();
}

void RobotCar::Run() {
    while (true) {
        float dist = ReadDistance();
        if (dist > 0 && dist < OBSTACLE_CM) {
            // detected
            StopMotors();        sleep_ms(200);
            MoveBackward(MAX_SPEED/2); sleep_ms(500);
            StopMotors();        sleep_ms(200);

            // 180
            if (turn_right_next_) Turn180Right(MAX_SPEED);
            else                    Turn180Left(MAX_SPEED);
            turn_right_next_ = !turn_right_next_;

            // forward back
            MoveForward(MAX_SPEED);
            sleep_ms(300);
            StopMotors();
            sleep_ms(200);
        }
        else {
            MoveForward(MAX_SPEED);
        }
        sleep_ms(50);
    }
}

void RobotCar::MoveForward(int speed) {
    Motor_Run(MOTORA, FORWARD, speed);
    Motor_Run(MOTORB, FORWARD, speed);
    Motor_Run(MOTORC, FORWARD, speed);
    Motor_Run(MOTORD, FORWARD, speed);
}

void RobotCar::MoveBackward(int speed) {
    Motor_Run(MOTORA, BACKWARD, speed);
    Motor_Run(MOTORB, BACKWARD, speed);
    Motor_Run(MOTORC, BACKWARD, speed);
    Motor_Run(MOTORD, BACKWARD, speed);
}

void RobotCar::StopMotors() {
    Motor_Stop(MOTORA);
    Motor_Stop(MOTORB);
    Motor_Stop(MOTORC);
    Motor_Stop(MOTORD);
}

void RobotCar::Turn90Right(int speed) {
    // Left forward, right backward
    Motor_Run(MOTORA, FORWARD, speed);
    Motor_Run(MOTORB, BACKWARD, speed);
    Motor_Run(MOTORC, FORWARD, speed);
    Motor_Run(MOTORD, BACKWARD, speed);
    sleep_ms(90 * MS_PER_DEG);
    StopMotors();
}

void RobotCar::Turn90Left(int speed) {
    // Left backward, right forward
    Motor_Run(MOTORA, BACKWARD, speed);
    Motor_Run(MOTORB, FORWARD, speed);
    Motor_Run(MOTORC, BACKWARD, speed);
    Motor_Run(MOTORD, FORWARD, speed);
    sleep_ms(90 * MS_PER_DEG);
    StopMotors();
}

void RobotCar::Turn180Right(int speed) {
    Turn90Right(speed);
    sleep_ms(50);
    Turn90Right(speed);
}

void RobotCar::Turn180Left(int speed) {
    Turn90Left(speed);
    sleep_ms(50);
    Turn90Left(speed);
}

float RobotCar::ReadDistance() {
    gpio_put(TRIG_PIN, 1);
    sleep_us(10);
    gpio_put(TRIG_PIN, 0);

    absolute_time_t t_start = get_absolute_time();
    while (!gpio_get(ECHO_PIN)) {
        if (absolute_time_diff_us(t_start, get_absolute_time()) > 30000) return -1;
    }
    absolute_time_t t0 = get_absolute_time();
    while (gpio_get(ECHO_PIN)) {
        if (absolute_time_diff_us(t0, get_absolute_time()) > 30000) break;
    }
    absolute_time_t t1 = get_absolute_time();

    uint32_t us = absolute_time_diff_us(t0, t1);
    return (us / 2.0f) / 29.1f;
}