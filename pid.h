#pragma once 
typedef struct PIDController {
    float *Kp, *Ki, *Kd;
    double error, derivative, integral;
} PIDController;

typedef struct {
    PIDController *direction, *distance;
    double command_left, command_right;
} PIDArchi;

void initPID(PIDController*, float*, float*, float*);
void resetPID(PIDController*);
void updatePID(PIDController*, float);
double getPIDOutput(PIDController*);

void initArchi(PIDArchi*, PIDController*, PIDController*);
void resetArchi(PIDArchi*, double, double);
void updateArchi(PIDArchi*, double, double);

double getArchiLeftOutput(PIDArchi*);
double getArchiRightOutput(PIDArchi*);

extern PIDController direction;
extern PIDController distance;
extern PIDArchi archi; 

extern float kP_distance;
extern float kD_distance; 
extern float kI_distance; 
extern float kP_direction;
extern float kD_direction;
extern float kI_direction;
