#ifndef DRIVETRAIN_SUBSYSTEM_H
#define DRIVETRAIN_SUBSYSTEM_H
#include "main.h"
#include "Constants.h"

class Drivetrain_Subsystem {
    private:
    //Motors
    pros::Motor m_left_front;
    pros::Motor m_left_rear;
    pros::Motor m_left_ext;
    pros::Motor m_right_front;
    pros::Motor m_right_rear;
    pros::Motor m_right_ext;

    pros::Motor_Group mg_left;
    pros::Motor_Group mg_right;
    
    //Sensors
    pros::ADIDigitalOut s_flaps_extension;

    //Variables
    bool isFlapsExtended;

    public:
    Drivetrain_Subsystem();

    void setBrakeMode(int mode);
    
    bool getExtensionStatus();

    void toggleExtensionState();

    void setExtensionState(bool value);

    void flapsControl(pros::Controller controller);

    void fieldOrientatedControl(pros::Controller controller);

    void joystickControl(pros::Controller controller); 

    void drivetrainControl(double leftMG, double rightMG);

    void stopControl();

    void printTask();
};

#endif