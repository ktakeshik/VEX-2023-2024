#include "intake_subsystem.h"

Intake_Subsystem::Intake_Subsystem ()
:   m_intake(Constants::Intake::MP_INTAKE), 
    s_intake_extension(Constants::Intake::SP_INTAKE)
{
    //Motor Configuration & Intialization
    pros::Motor m_intake_configurator(Constants::Intake::MP_INTAKE,
        MOTOR_GEARSET_06, Constants::Intake::M_INTAKE_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);

    isIntakeOut = false;
    
    m_intake_configurator.set_brake_mode(Constants::Intake::M_INTAKE_BRAKE_MODE);
}

bool Intake_Subsystem::getExtension(){
    return isIntakeOut;
}

void Intake_Subsystem::toggleExtension(){
    isIntakeOut = !isIntakeOut;
    s_intake_extension.set_value(isIntakeOut);
}

void Intake_Subsystem::setExtension(bool value){
    s_intake_extension.set_value(value);
    isIntakeOut = value;
}

void Intake_Subsystem::intakeControl(float percentOut){
    percentOut *= 600;
    m_intake.move_velocity(percentOut);
}

void Intake_Subsystem::printTask() 
{
    // pros::lcd::print(1, "LEFTMG: %f", m_left_rear.get_actual_velocity());
	// pros::lcd::print(2, "RIGHTMG: %f", m_right_rear.get_actual_velocity());
}

