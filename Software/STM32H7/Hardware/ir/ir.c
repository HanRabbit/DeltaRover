#include "ir.h"

#include "../buzzer/buzzer.h"
#include "../motor/motor.h"

#define BASE_SPEED 80
#define KP 20  // 比例系数，可根据实际调整

#define BLACK 1
#define WHITE 0

const float weights[7] = {-4, -2, -.6f, 0, .6f, 2, 4};

enum {
    IR_FORWARD = 0,
    IR_ON,
    IR_STOP
};

void ir_update(void) {
    motor_set_speed(100, 100); // 启动电机
    while (!IR_L1 && !IR_L2 && !IR_L3 && !IR_M && !IR_R1 && !IR_R2 && !IR_R3) {
        while (!IR_L1 && !IR_L2 && !IR_L3 && !IR_M && !IR_R1 && !IR_R2 && !IR_R3) {};
        HAL_Delay(50);
    }
    BUZZER_TOGGLE(100);

    while (IR_L1 || IR_L2 || IR_L3 || IR_M || IR_R1 || IR_R2 || IR_R3) {
        ir_control(); // 调用红外传感器控制函数
    }
    motor_set_speed(0, 0); // 停止电机
    BUZZER_TOGGLE(100);

    motor_set_position(-1780, 1780, 30);

    motor_set_speed(100, 100); // 启动电机
    while (!IR_L1 && !IR_L2 && !IR_L3 && !IR_M && !IR_R1 && !IR_R2 && !IR_R3) {
        while (!IR_L1 && !IR_L2 && !IR_L3 && !IR_M && !IR_R1 && !IR_R2 && !IR_R3) {};
        HAL_Delay(50);
    }
    BUZZER_TOGGLE(100);

    while (IR_L1 || IR_L2 || IR_L3 || IR_M || IR_R1 || IR_R2 || IR_R3) {
        ir_control(); // 调用红外传感器控制函数
    }
    motor_set_speed(0, 0); // 停止电机
    BUZZER_TOGGLE(300);

    motor_set_position(2000, -2000, 30);
}

void ir_control(void) {
    const uint8_t ir[7] = {IR_L3, IR_L2, IR_L1, IR_M, IR_R1, IR_R2, IR_R3};

    float sum = 0, count = 0;
    for (int i = 0; i < 7; i++) {
        if (ir[i] == BLACK) {
            sum += weights[i];
            count++;
        }
    }

    float error = 0;
    if (count > 0) {
        error = sum * 100 / count; // 平滑化处理
    }

    // 计算左右轮速度
    int left_speed = BASE_SPEED + KP * error / 100;
    int right_speed = BASE_SPEED - KP * error / 100;

    // 限幅
    if (left_speed > 100) left_speed = 100;
    if (left_speed < 0) left_speed = 0;
    if (right_speed > 100) right_speed = 100;
    if (right_speed < 0) right_speed = 0;

    motor_set_speed(left_speed, right_speed);
}