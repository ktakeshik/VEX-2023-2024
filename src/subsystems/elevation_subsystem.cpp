#include "elevation_subsystem.h"

Elevation_Subsystem::Elevation_Subsystem ()
:   s_arm_extension(ElevationConstants::SP_ARM)
{
    //Motor Configuration & Intialization
    pros::Motor m_intake_configurator(IntakeConstants::MP_INTAKE,
        MOTOR_GEARSET_06, IntakeConstants::M_INTAKE_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);

    isArmOut = false;
    
    m_intake_configurator.set_brake_mode(IntakeConstants::M_INTAKE_BRAKE_MODE);
}

bool Elevation_Subsystem::getExtension()
{
    return isArmOut;
}

void Elevation_Subsystem::toggleExtension()
{
    isArmOut = !isArmOut;
    s_arm_extension.set_value(isArmOut);
}

void Elevation_Subsystem::setExtension(bool value)
{
    s_arm_extension.set_value(value);
    isArmOut = value;
}

void Elevation_Subsystem::printTask() 
{
    // pros::lcd::print(1, "LEFTMG: %f", m_left_rear.get_actual_velocity());
	// pros::lcd::print(2, "RIGHTMG: %f", m_right_rear.get_actual_velocity());
}
