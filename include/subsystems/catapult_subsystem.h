#ifndef CATAPULT_SUBSYSTEM_H
#define CATAPULT_SUBSYSTEM_H
#include "main.h"
#include "Constants.h"

class Catapult_Subsystem {
    private:
    //Motors
    pros::Motor m_catapult;

    //Sensors
    pros::Rotation s_rotation;

    public:
    Catapult_Subsystem();

    bool isCatapultDown();

    void catapultControl(pros::Controller controller, bool intakeOut);

    void autoCatapultMovement(pros::Controller controller, bool intakeOut);

    void printTask();
};

#endif