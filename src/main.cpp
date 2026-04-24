#include <Arduino.h>
#include "pins_map.h"

/**
 * @brief Drive the motor with a specific speed and direction.
 * 
 * @param speed Range from -255 (full reverse) to 255 (full forward). 
 *              0 performs braking logic.
 */
void drive(int speed) {
    // 1. Constrain speed to -255 ~ 255
    speed = constrain(speed, -255, 255);

    // 2. Control STBY pin (High to enable driver)
    digitalWrite(MOTOR_STBY, HIGH);

    if (speed > 0) {
        // Forward: AIN1=H, AIN2=L
        digitalWrite(MOTOR_AIN1, HIGH);
        digitalWrite(MOTOR_AIN2, LOW);
        analogWrite(MOTOR_PWM, speed);
    } else if (speed < 0) {
        // Reverse: AIN1=L, AIN2=H
        digitalWrite(MOTOR_AIN1, LOW);
        digitalWrite(MOTOR_AIN2, HIGH);
        analogWrite(MOTOR_PWM, abs(speed));
    } else {
        // Brake: AIN1=H, AIN2=H (Short Brake)
        digitalWrite(MOTOR_AIN1, HIGH);
        digitalWrite(MOTOR_AIN2, HIGH);
        analogWrite(MOTOR_PWM, 0);
    }
}

void setup() {
    Serial.begin(115200);

    // Initialize Pins
    pinMode(MOTOR_AIN1, OUTPUT);
    pinMode(MOTOR_AIN2, OUTPUT);
    pinMode(MOTOR_PWM, OUTPUT);
    pinMode(MOTOR_STBY, OUTPUT);

    Serial.println("H-Bridge Motor Control Initialized.");
}

void loop() {
    // Sequencer as requested:
    // 全速前進 2s -> 急煞 0.5s -> 半速後退 1s -> 空轉
    
    Serial.println("Full speed forward for 2s...");
    drive(255);
    delay(2000);

    Serial.println("Brake for 0.5s...");
    drive(0);
    delay(500);

    Serial.println("Half speed reverse for 1s...");
    drive(-128);
    delay(1000);

    Serial.println("Coast (Standby)...");
    digitalWrite(MOTOR_STBY, LOW); // Entering Standby effectively coasts the motor
    delay(2000);
}
