// #include "Servo.h"
// #include "hardware/pwm.h"
// #include <algorithm>
// #include <cmath>

// Servo::Servo(uint pin)
//     : servo_pin(pin),
//       current_angle(-1.0f),
//       min_u16_duty(1638),    // default ~0.5ms @ 20ms period
//       max_u16_duty(7864),    // default ~2.5ms @ 20ms period
//       min_angle(0.0f),
//       max_angle(180.0f)
// {
//     // prepare PWM on the pin
//     gpio_set_function(servo_pin, GPIO_FUNC_PWM);
//     pwm_slice = pwm_gpio_to_slice_num(servo_pin);

//     // configure for ~50Hz (20ms period)
//     pwm_config config = pwm_get_default_config();
//     pwm_config_set_clkdiv(&config, 64.0f);
//     pwm_config_set_wrap(&config, 20000);
//     pwm_init(pwm_slice, &config, true);

//     // compute conversion factor
//     angle_conversion_factor = float(max_u16_duty - min_u16_duty) / (max_angle - min_angle);

//     // initialize at 0°
//     set_angle(0.0f);
// }

// void Servo::update_settings(uint16_t min_duty, uint16_t max_duty, float min_ang, float max_ang) {
//     min_u16_duty = min_duty;
//     max_u16_duty = max_duty;
//     min_angle = min_ang;
//     max_angle = max_ang;
//     angle_conversion_factor = float(max_u16_duty - min_u16_duty) / (max_angle - min_angle);
// }

// void Servo::set_angle(float angle) {
//     // clamp to range
//     float clamped = std::clamp(angle, min_angle, max_angle);
//     // round to 2 decimal places
//     clamped = std::round(clamped * 100.0f) / 100.0f;

//     if (clamped == current_angle) { 
//         return;
// }
//     current_angle = clamped;
//     uint16_t duty = angle_to_duty(current_angle);
//     pwm_set_gpio_level(servo_pin, duty);
// }

// uint16_t Servo::angle_to_duty(float angle) const {
//     return uint16_t((angle - min_angle) * angle_conversion_factor + min_u16_duty);
// }