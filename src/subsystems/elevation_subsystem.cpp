#include "elevation_subsystem.h"

Elevation_Subsystem::Elevation_Subsystem ()
:   s_arm_extension(Constants::Elevation::SP_ARM)
{
    //Motor Configuration & Intialization
    pros::Motor m_intake_configurator(Constants::Intake::MP_INTAKE,
        MOTOR_GEARSET_06, Constants::Intake::M_INTAKE_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);

    isArmOut = false;
    
    m_intake_configurator.set_brake_mode(Constants::Intake::M_INTAKE_BRAKE_MODE);
}

bool Elevation_Subsystem::getExtensionStatus(){
    return isArmOut;
}

void Elevation_Subsystem::toggleExtensionState(){
    isArmOut = !isArmOut;
    s_arm_extension.set_value(isArmOut);
}

void Elevation_Subsystem::setExtensionState(bool value){
    s_arm_extension.set_value(value);
    isArmOut = value;
}

void Elevation_Subsystem::elevationControl(pros::Controller controller){
    if (controller.get_digital(DIGITAL_LEFT)) {
        toggleExtensionState();
        while(controller.get_digital(DIGITAL_LEFT)){
            pros::delay(20);
        }
    }
}

void Elevation_Subsystem::printTask() 
{
    // pros::lcd::print(1, "LEFTMG: %f", m_left_rear.get_actual_velocity());
	// pros::lcd::print(2, "RIGHTMG: %f", m_right_rear.get_actual_velocity());
}

