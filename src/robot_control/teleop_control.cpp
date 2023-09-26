#include "robot_control/teleop_control.h"

void Teleoperation_Control::catapultControl()
{
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    if (!s_Intake.getExtension()) {
        return;
    }

    switch (s_Catapult.getCatapultState()) 
    {
        case Catapult_Subsystem::DEFAULT_STATE:
            if (!s_Catapult.isCatapultDown()) {
                s_Catapult.catapultControl(0.86);
            }
            else {
                s_Catapult.stopCatapult();
            }
            break;

        case Catapult_Subsystem::LAUNCH_TRIBALL:
            if (!s_Catapult.isCatapultUp()) {
                s_Catapult.catapultControl(1);
            }
            else {
                s_Catapult.stopCatapult();
            }
            break;

        case Catapult_Subsystem::POSSESS_TRIBALL:
            if (!s_Catapult.isCatapultMiddle()) {
                s_Catapult.catapultControl(0.6);
            }
            else {
                s_Catapult.stopCatapult();
            }
            break;
        
        case Catapult_Subsystem::MATCH_LOAD:
            while (s_Catapult.getSaftey()) 
            {
                s_Catapult.catapultControl(1);
            }
            s_Catapult.stopCatapult();
            break;

        case Catapult_Subsystem::STAY_UP:
            break;
    }
}

void Teleoperation_Control::teleopControl()
{
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    while(true)
    {
        pros::delay(20);
        
        /*******************************************************************
        *
        * Drivetrain Control
        * 
        ********************************************************************/

        s_Drivetrain.joystickControl(master);

        if (master.get_digital_new_press(DIGITAL_DOWN)) {
            s_Drivetrain.toggleExtension();
        }

        /*******************************************************************
        *
        * Elevation Toggle
        * 
        ********************************************************************/

        if (master.get_digital_new_press(DIGITAL_UP)) {
            s_Elevation.toggleExtension();
        }
    
        /*******************************************************************
        *
        * Intake Control
        * 
        ********************************************************************/
        
        if (master.get_digital(DIGITAL_L1)) {
            s_Intake.intakeControl(1);
        }
        else if (master.get_digital(DIGITAL_L2)) {
            s_Intake.intakeControl(-1);
        }
        else {
            s_Intake.intakeControl(0);
        }

        if (master.get_digital_new_press(DIGITAL_RIGHT)) {
            s_Intake.toggleExtension();
        }

        /*******************************************************************
        *
        * Catapult Control
        * 
        ********************************************************************/

        if (master.get_digital(DIGITAL_R1)) {
            s_Catapult.setCatapultState(Catapult_Subsystem::LAUNCH_TRIBALL);
        }
        else if (master.get_digital_new_press(DIGITAL_R2)) {
            s_Catapult.toggleSaftey();
            s_Catapult.setCatapultState(Catapult_Subsystem::MATCH_LOAD);
        }
        else if (!master.get_digital_new_press(DIGITAL_R1)
            && !master.get_digital(DIGITAL_R2) 
            && !s_Catapult.getSaftey()) {
            s_Catapult.setCatapultState(Catapult_Subsystem::DEFAULT_STATE);
        }

        if (master.get_digital_new_press(DIGITAL_LEFT)) {
            s_Catapult.toggleSaftey();
        } 
       
    }
}

void Teleoperation_Control::testCode()
{
    
}