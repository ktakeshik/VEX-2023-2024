#ifndef INTAKE_SUBSYSTEM_H
#define INTAKE_SUBSYSTEM_H
#include "main.h"
#include "Constants.h"
#include "aSClib\subsystem_base.h"

class Intake_Subsystem : public Subsystem_Base {
    private:
    //Motors
    pros::Motor m_intake;
    
    pros::ADIDigitalOut s_intake_extension;

    //Variables
    bool isIntakeOut;

    public:
    Intake_Subsystem();

    bool getExtension();

    void toggleExtension();

    void setExtension(bool value);

    void intakeControl(float percentOut);

    void printTask();

    void periodic() override;

    void shutdown() override;
};

#endif