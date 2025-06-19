#include "ir.h"

#include "../buzzer/buzzer.h"
#include "../motor/motor.h"

#define CAR_IR_SPEED 80
#define CAR_IR_DIFFERENCE 40

enum {
    state_forward = 0,
    state_ir,
    state_stop,
} state = state_forward;

/**
* if (IR_O2) {
        motor_r_set_speed(CAR_IR_SPEED - CAR_IR_DIFFERENCE);
        motor_l_set_speed(CAR_IR_SPEED);
    } else if (IR_O3) {
        motor_r_set_speed(CAR_IR_SPEED);
        motor_l_set_speed(CAR_IR_SPEED - CAR_IR_DIFFERENCE);
    } else {
        motor_r_set_speed(CAR_IR_SPEED);
        motor_l_set_speed(CAR_IR_SPEED);
    }

    motor_set_speed(60, 60);
    if (!IR_O2 || !IR_O3 || !IR_O1 || !IR_O4) {
        motor_set_speed(0, 0);

        MOTOR_DISABLE();
        BUZZER_ON();
        HAL_Delay(1000);
        BUZZER_OFF();

        return;
    }
 */
void ir_control(void) {
    if (state == state_forward) {
        motor_set_speed(40, 40);
        if (IR_O2 || IR_O3 || IR_O1 || IR_O4) {
            state = state_ir;
        }
    }

    if (state == state_ir) {
        if (IR_O3) {
            motor_r_set_speed(CAR_IR_SPEED - CAR_IR_DIFFERENCE);
            motor_l_set_speed(CAR_IR_SPEED);
        } else if (IR_O2) {
            motor_r_set_speed(CAR_IR_SPEED);
            motor_l_set_speed(CAR_IR_SPEED - CAR_IR_DIFFERENCE);
        } else if (IR_O2 || IR_O3) {
            motor_r_set_speed(CAR_IR_SPEED);
            motor_l_set_speed(CAR_IR_SPEED);
        } else if (!IR_O1 && !IR_O2) {
            state = state_forward;
        }
    }
}
