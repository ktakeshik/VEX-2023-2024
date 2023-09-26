#include "pid_controller.h"

void PID_Controller::resetController() {
    previousError = 0;
    integral = 0;
}

void PID_Controller::setTolerance(float nativeUnits) {
    tolerance = {nativeUnits};
}

void PID_Controller::setPGain(float kP) {
    proportionalGain = {kP};
}

void PID_Controller::setIGain(float kI) {
    integralGain = {kI};
}

void PID_Controller::setDGain(float kD) {
    derivativeGain = {kD};
}

void PID_Controller::setFFGain(float kFF) {
    feedFowardGain = {kFF};
}

void PID_Controller::setError(float value) {
    error = value;
}

void PID_Controller::setSP(float SP) {
    setPoint = {SP};
    previousError = {0};
}

void PID_Controller::setPV(float PV) {
    processVariable = {PV};
}

double PID_Controller::getError() {
    return error;
}

double PID_Controller::getOutput() {
    if (error < tolerance) {
        return 0;
    }

    integral += error;
    derivative = {error - previousError};

    output = proportionalGain * error 
        + integralGain * integral 
        + derivativeGain * derivative;
    
    previousError = {error};

    return output;
}