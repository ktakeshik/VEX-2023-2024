#ifndef ELEVATION_SUBSYSTEM_H
#define ELEVATION_SUBSYSTEM_H
#include "main.h"
#include "Constants.h"

class Elevation_Subsystem {
    private:
    
    pros::ADIDigitalOut s_arm_extension;

    //Variables
    bool isArmOut;

    public:
    Elevation_Subsystem();

    bool getExtensionStatus();

    void toggleExtensionState();

    void setExtensionState(bool value);

    void elevationControl(pros::Controller controller);

    void printTask();
};

#endif