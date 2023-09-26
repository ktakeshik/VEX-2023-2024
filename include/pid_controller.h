#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include "main.h"
#include "constants.h"

class PID_Controller {
    private:

    float proportionalGain;
    float integralGain;
    float integral;
    float derivativeGain;
    float derivative;
    float feedFowardGain;
    float setPoint;
    float processVariable;
    float error;
    float previousError;
    double output;
    float tolerance;

    public:

    void resetController();

    void setTolerance(float nativeUnits);

    void setPGain(float kP);

    void setIGain(float kI);

    void setDGain(float kD);

    void setFFGain(float kFF);

    void setError(float value);

    void setSP(float SP);

    void setPV(float PV);

    double getAcceleration(float previousRate, float currentRate);

    double getError();

    double getOutput();

    void printTask();
};

#endif