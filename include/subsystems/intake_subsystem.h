#ifndef INTAKE_SUBSYSTEM_H
#define INTAKE_SUBSYSTEM_H
#include "main.h"
#include "Constants.h"

class Intake_Subsystem {
    private:
    //Motors
    pros::Motor m_intake;
    
    pros::ADIDigitalOut s_intake_extension;

    //Variables
    bool isIntakeOut;

    public:
    Intake_Subsystem();

    bool getExtensionStatus();

    void toggleExtensionState();

    void setExtensionState(bool value);

    void intakeExtensionControl(pros::Controller controller);

    void intakeControl(pros::Controller controller);

    void printTask();
};

#endif