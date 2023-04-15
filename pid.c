#include "pid.h"
PIDController center;
PIDController left;
PIDController right;
PIDArchi archi; 

float kP_right=1;
float kD_right=0; 
float kI_right=0; 
float kP_left=1;
float kD_left=0;
float kI_left=0;
float kP_center=1;
float kD_center=0;
float kI_center=0;


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
    PID->derivative = error - PID->error;
    PID->integral += error;
    PID->error = error;
}

double getPIDOutput(PIDController* PID) {
    return (*PID->Kp) * PID->error + (*PID->Ki) * PID->integral + (*PID->Kd) * PID->derivative;
}

void initArchi(PIDArchi* ARCH, PIDController* left, PIDController* right, PIDController* central) {
    ARCH->left = left;
    ARCH->right = right;
    ARCH->central = central;
};


void resetArchi(PIDArchi* ARCH, double left_command, double right_command) {
    resetPID(ARCH->left);
    resetPID(ARCH->right);
    resetPID(ARCH->central);
    ARCH->command_left = left_command;
    ARCH->command_right = right_command;
};

void updateArchi(PIDArchi* ARCH, double left, double right) {
    updatePID(ARCH->left, ARCH->command_left - left);
    updatePID(ARCH->right, ARCH->command_right - right);
    updatePID(ARCH->central, left / ARCH->command_left - right / ARCH->command_right);
};

double getArchiLeftOutput(PIDArchi* ARCH) {
    return getPIDOutput(ARCH->left) - getPIDOutput(ARCH->central);
};

double getArchiRightOutput(PIDArchi* ARCH) {
    return getPIDOutput(ARCH->right) + getPIDOutput(ARCH->central);
};
