#include "drivetrain_subsystem.h"

Drivetrain_Subsystem::Drivetrain_Subsystem ()
:   m_left_front(Constants::Drivetrain::MP_LEFT_FRONT), 
    m_left_rear(Constants::Drivetrain::MP_LEFT_REAR),
    m_left_ext(Constants::Drivetrain::MP_LEFT_EXT), 
    m_right_front(Constants::Drivetrain::MP_RIGHT_FRONT), 
    m_right_rear(Constants::Drivetrain::MP_RIGHT_REAR),
    m_right_ext(Constants::Drivetrain::MP_RIGHT_EXT),
    mg_left({m_left_front, m_left_rear}),
    mg_right({m_right_front, m_right_rear}),
    s_flaps_extension{Constants::Drivetrain::SP_FLAPS}
{
    //Motor Configuration & Intialization
    pros::Motor m_left_front_configurator(Constants::Drivetrain::MP_LEFT_FRONT,
        MOTOR_GEARSET_06, Constants::Drivetrain::M_LEFT_FRONT_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);
    
    pros::Motor m_left_rear_configurator(Constants::Drivetrain::MP_LEFT_REAR,
        MOTOR_GEARSET_06, Constants::Drivetrain::M_LEFT_REAR_REVERSED,
        MOTOR_ENCODER_ROTATIONS);

    pros::Motor m_left_ext_configurator(Constants::Drivetrain::MP_LEFT_EXT,
        MOTOR_GEARSET_06, Constants::Drivetrain::M_LEFT_EXT_REVERSED,
        MOTOR_ENCODER_ROTATIONS);

    pros::Motor m_right_front_configurator(Constants::Drivetrain::MP_RIGHT_FRONT, 
        MOTOR_GEARSET_06, Constants::Drivetrain::M_RIGHT_FRONT_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);
    
    
    pros::Motor m_right_rear_configurator(Constants::Drivetrain::MP_RIGHT_REAR, 
        MOTOR_GEARSET_06, Constants::Drivetrain::M_RIGHT_REAR_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);

    pros::Motor m_right_ext_configurator(Constants::Drivetrain::MP_RIGHT_EXT,
        MOTOR_GEARSET_06, Constants::Drivetrain::M_RIGHT_EXT_REVERSED,
        MOTOR_ENCODER_ROTATIONS);

    mg_left.set_brake_modes(Constants::Drivetrain::MG_LEFT_BRAKE_MODE);
    mg_right.set_brake_modes(Constants::Drivetrain::MG_RIGHT_BRAKE_MODE);

    m_left_ext.set_brake_mode(Constants::Drivetrain::MG_LEFT_BRAKE_MODE);
    m_right_ext.set_brake_mode(Constants::Drivetrain::MG_RIGHT_BRAKE_MODE);

    mg_left.set_reversed(Constants::Drivetrain::MG_LEFT_REVERSED);
    mg_right.set_reversed(Constants::Drivetrain::MG_RIGHT_REVERSED);
}

void Drivetrain_Subsystem::setBrakeMode(int mode)
{
    pros::motor_brake_mode_e_t brake_mode[3] = {pros::E_MOTOR_BRAKE_COAST, pros::E_MOTOR_BRAKE_BRAKE, pros::E_MOTOR_BRAKE_HOLD};
    mg_left.set_brake_modes(brake_mode[mode]);
    mg_right.set_brake_modes(brake_mode[mode]);
}

bool Drivetrain_Subsystem::getExtensionStatus(){
    return isFlapsExtended; 
}

void Drivetrain_Subsystem::toggleExtensionState(){
    isFlapsExtended = !isFlapsExtended;
    s_flaps_extension.set_value(isFlapsExtended);
}

void Drivetrain_Subsystem::setExtensionState(bool value){
    s_flaps_extension.set_value(value);
    isFlapsExtended = value;
}

void Drivetrain_Subsystem::flapsControl(pros::Controller controller){
    if (controller.get_digital(DIGITAL_UP)){
        toggleExtensionState();
        while(controller.get_digital(DIGITAL_UP)){
            pros::delay(20);
        }
    }
}

void Drivetrain_Subsystem::joystickControl(pros::Controller controller) 
{
    mg_left.move(controller.get_analog(ANALOG_LEFT_Y));
    m_left_ext.move(controller.get_analog(ANALOG_LEFT_Y)); 
    mg_right.move(controller.get_analog(ANALOG_RIGHT_Y)); 
    m_right_ext.move(controller.get_analog(ANALOG_RIGHT_Y));
}

void Drivetrain_Subsystem::drivetrainControl(double leftMG, double rightMG)
{
    mg_left.move_velocity(leftMG);
    mg_right.move_velocity(rightMG) ;
}

void Drivetrain_Subsystem::stopControl()
{
    mg_left.brake();
    mg_right.brake();
}

void Drivetrain_Subsystem::printTask() 
{
    // pros::lcd::print(1, "LEFTMG: %f", m_left_rear.get_actual_velocity());
	// pros::lcd::print(2, "RIGHTMG: %f", m_right_rear.get_actual_velocity());
}

