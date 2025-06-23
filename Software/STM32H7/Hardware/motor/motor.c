#include "motor.h"

__IO int32_t encoder1_speed = 0;
__IO int32_t encoder2_speed = 0;

PID_t motor_l_speed_pid;
PID_t motor_r_speed_pid;
PID_t motor_l_position_pid;
PID_t motor_r_position_pid;

__IO int32_t motor_l_position = 0;
__IO int32_t motor_r_position = 0;

bool motor_enable_position = true; // 是否启用位置环控制

void motor_init(void) {
    /* 电机速度环控制器初始化 */
    pid_init(&motor_l_speed_pid, 0.22f, 1.0f, 0.04f, 0.01f);
    pid_init(&motor_r_speed_pid, 0.22f, 1.0f, 0.04f, 0.01f);

    pid_set_mode(&motor_l_speed_pid, PID_MODE_SPEED);
    pid_set_mode(&motor_r_speed_pid, PID_MODE_SPEED);

    pid_set_output_limits(&motor_l_speed_pid, -3600.0f, 3600.0f);
    pid_set_output_limits(&motor_r_speed_pid, -3600.0f, 3600.0f);

    pid_set_integral_limits(&motor_l_speed_pid, -0.001f, 0.001f);
    pid_set_integral_limits(&motor_r_speed_pid, -0.001f, 0.001f);

    /* 电机位置环控制器初始化 */
    pid_init(&motor_l_position_pid, .094f, 0.0f, 0.0046f, 0.01f);
    pid_init(&motor_r_position_pid, .094f, 0.0f, 0.0046f, 0.01f);

    pid_set_output_limits(&motor_l_position_pid, -100.0f, 100.0f); // 设置位置环输出限幅
    pid_set_output_limits(&motor_r_position_pid, -100.0f, 100.0f); // 设置位置环输出限幅

    motor_l_position = 0;
    motor_r_position = 0;
}

void motor_l_set_speed(const int32_t speed) { motor_l_speed_pid.target = (float) speed; }
void motor_r_set_speed(const int32_t speed) { motor_r_speed_pid.target = (float) speed; }

void motor_set_speed(const int32_t l_speed, const int32_t r_speed) {
    motor_enable_position = false;  // 禁用位置环控制
    motor_l_set_speed(l_speed);
    motor_r_set_speed(r_speed);
}

void motor_set_position(const int32_t l_pos, const int32_t r_pos, const int32_t speed) {
    motor_position_reset();
    motor_enable_position = true; // 启用位置环控制
    motor_l_position_pid.target = (float) l_pos;
    motor_r_position_pid.target = (float) r_pos;
    pid_set_output_limits(&motor_l_position_pid, -speed, speed);
    pid_set_output_limits(&motor_r_position_pid, -speed, speed);
    while (fabsf(motor_l_position_pid.error) > MOTOR_DIE_AREA || fabsf(motor_r_position_pid.error) > MOTOR_DIE_AREA);
}

float motor_pulse_to_m(void) {
    /* 65mm = 0.065m */
    const float l = (float) (0.065f * M_PI);
    return (float) motor_l_position / 1560.0f / 5 * l;
}

int32_t motor_m_to_pulse(const float m) {
    const float l = (float) (0.065f * M_PI);
    return (int32_t) (m * 1560.0f * 5 / l);
}

void motor_set_forward(const float m, const int32_t speed) {
    motor_set_position(motor_m_to_pulse(m), motor_m_to_pulse(m), speed);
}

void motor_position_reset(void) {
    motor_l_position = 0;
    motor_r_position = 0;
    // 重置位置环 PID 控制器
    motor_l_position_pid.target = 0.0f;
    motor_r_position_pid.target = 0.0f;
    motor_l_speed_pid.target = 0.0f;
    motor_r_speed_pid.target = 0.0f;
    motor_l_speed_pid.output = 0.0f;
    motor_r_speed_pid.output = 0.0f;
    motor_r_speed_pid.last_output = 0.0f;
    motor_l_speed_pid.last_output = 0.0f;
    pid_set_output_limits(&motor_l_position_pid, -100.0f, 100.0f);
    pid_set_output_limits(&motor_r_position_pid, -100.0f, 100.0f);
}

void motor_update(void) {
    motor_l_position += encoder1_speed * MOTOR_UPDATE_FREQ;
    motor_r_position += encoder2_speed * MOTOR_UPDATE_FREQ;

    // 更新位置环 PID 控制器
    if (motor_enable_position) {
        motor_l_set_speed(pid_update(&motor_l_position_pid, motor_l_position));
        motor_r_set_speed(pid_update(&motor_r_position_pid, motor_r_position));
    }    MOTOR_L_PWM((int32_t) pid_update(&motor_l_speed_pid, encoder1_speed));
    MOTOR_R_PWM((int32_t) pid_update(&motor_r_speed_pid, encoder2_speed));
}
