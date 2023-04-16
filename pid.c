#include "pid.h"
PIDController distance;
PIDController direction;
PIDArchi archi; 
/*
float kP_right=1;
float kD_right=0; 
float kI_right=0; 
float kP_left=1;
float kD_left=0;
float kI_left=0;
float kP_center=1;
float kD_center=0;
float kI_center=0;
*/

void initPID(PIDController* PID, float* Kp, float* Ki, float* Kd) {
    PID->Kp = Kp;
    PID->Ki = Ki;
    PID->Kd = Kd;
    PID->error = 0.f;
    PID->derivative = 0.f;
    PID->integral = 0.f;
}

void resetPID(PIDController* PID) {
    PID->error = 0.f;
    PID->derivative = 0.f;
    PID->integral = 0.f;
}

void updatePID(PIDController* PID, float error) {
    PID->derivative = error - PID->error / 0.005;
    PID->integral += error * 0.005;
    PID->error = error;
}

double getPIDOutput(PIDController* PID) {
    return (*PID->Kp) * PID->error + (*PID->Ki) * PID->integral + (*PID->Kd) * PID->derivative;
}

void initArchi(PIDArchi* ARCH, PIDController* distance, PIDController* direction) {
    ARCH->distance = distance;
    ARCH->direction = direction;
};


void resetArchi(PIDArchi* ARCH, double left_command, double right_command) {
    resetPID(ARCH->distance);
    resetPID(ARCH->direction);
    ARCH->command_distance = .5 * (left_command + right_command);
    ARCH->command_direction = .5 * (right_command - left_command);
};

void updateArchi(PIDArchi* ARCH, double left, double right) {
    updatePID(ARCH->distance, ARCH.command_distance - .5 * (left + right);
    updatePID(ARCH->direction, ARCH->command_direction - .5 * (right - left);
};

double getArchiLeftOutput(PIDArchi* ARCH) {
    return getPIDOutput(ARCH->distance) + getPIDOutput(ARCH->direction);
};

double getArchiRightOutput(PIDArchi* ARCH) {
    return getPIDOutput(ARCH->distance) - getPIDOutput(ARCH->direction);
};
