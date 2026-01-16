// #ifndef SERVO_H
// #define SERVO_H

// #include "pico/stdlib.h"

// class Servo {
// public:
//     explicit Servo(uint pin = 16);

//     // update mapping from angle to PWM duty
//     void update_settings(uint16_t min_duty, uint16_t max_duty, float min_ang, float max_ang);

//     // set servo position in degrees
//     void set_angle(float angle);

// private:
//     uint servo_pin;
//     uint pwm_slice;
//     float current_angle;

//     // calibration parameters
//     uint16_t min_u16_duty;
//     uint16_t max_u16_duty;
//     float min_angle;
//     float max_angle;
//     float angle_conversion_factor;

//     // convert an angle (deg) to PWM duty value
//     uint16_t angle_to_duty(float angle) const;
// };

// #endif // SERVO_H