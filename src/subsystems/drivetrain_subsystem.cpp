#include "drivetrain_subsystem.h"

Drivetrain_Subsystem::Drivetrain_Subsystem ()
:   m_left_front(DrivetrainConstants::MP_LEFT_FRONT), 
    m_left_rear(DrivetrainConstants::MP_LEFT_REAR),
    m_left_ext(DrivetrainConstants::MP_LEFT_EXT), 
    m_right_front(DrivetrainConstants::MP_RIGHT_FRONT), 
    m_right_rear(DrivetrainConstants::MP_RIGHT_REAR),
    m_right_ext(DrivetrainConstants::MP_RIGHT_EXT),
    mg_left({m_left_front, m_left_rear}),
    mg_right({m_right_front, m_right_rear}),
    s_flaps_extension{DrivetrainConstants::SP_FLAPS}
{
    //Motor Configuration & Intialization
    pros::Motor m_left_front_configurator(DrivetrainConstants::MP_LEFT_FRONT,
        MOTOR_GEARSET_06, DrivetrainConstants::M_LEFT_FRONT_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);
    
    pros::Motor m_left_rear_configurator(DrivetrainConstants::MP_LEFT_REAR,
        MOTOR_GEARSET_06, DrivetrainConstants::M_LEFT_REAR_REVERSED,
        MOTOR_ENCODER_ROTATIONS);

    pros::Motor m_left_ext_configurator(DrivetrainConstants::MP_LEFT_EXT,
        MOTOR_GEARSET_06, DrivetrainConstants::M_LEFT_EXT_REVERSED,
        MOTOR_ENCODER_ROTATIONS);

    pros::Motor m_right_front_configurator(DrivetrainConstants::MP_RIGHT_FRONT, 
        MOTOR_GEARSET_06, DrivetrainConstants::M_RIGHT_FRONT_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);
    
    
    pros::Motor m_right_rear_configurator(DrivetrainConstants::MP_RIGHT_REAR, 
        MOTOR_GEARSET_06, DrivetrainConstants::M_RIGHT_REAR_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);

    pros::Motor m_right_ext_configurator(DrivetrainConstants::MP_RIGHT_EXT,
        MOTOR_GEARSET_06, DrivetrainConstants::M_RIGHT_EXT_REVERSED,
        MOTOR_ENCODER_ROTATIONS);

    mg_left.set_brake_modes(DrivetrainConstants::MG_LEFT_BRAKE_MODE);
    mg_right.set_brake_modes(DrivetrainConstants::MG_RIGHT_BRAKE_MODE);

    m_left_ext.set_brake_mode(DrivetrainConstants::MG_LEFT_BRAKE_MODE);
    m_right_ext.set_brake_mode(DrivetrainConstants::MG_RIGHT_BRAKE_MODE);

    mg_left.set_reversed(DrivetrainConstants::MG_LEFT_REVERSED);
    mg_right.set_reversed(DrivetrainConstants::MG_RIGHT_REVERSED);

    mg_left.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
    mg_right.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
}

void Drivetrain_Subsystem::zeroOutMotors()
{
    mg_left.set_zero_position(0);
    m_left_ext.set_zero_position(0);
    mg_right.set_zero_position(0);
    m_right_ext.set_zero_position(0);
}

void Drivetrain_Subsystem::setBrakeMode(int mode)
{
    pros::motor_brake_mode_e_t brake_mode[3] = {pros::E_MOTOR_BRAKE_COAST, pros::E_MOTOR_BRAKE_BRAKE, pros::E_MOTOR_BRAKE_HOLD};
    mg_left.set_brake_modes(brake_mode[mode]);
    m_left_ext.set_brake_mode(brake_mode[mode]);
    mg_right.set_brake_modes(brake_mode[mode]);
    m_right_ext.set_brake_mode(brake_mode[mode]);
}

double Drivetrain_Subsystem::getLeftPost() 
{
    return m_left_front.get_position() / DrivetrainConstants::GEAR_REDUCTION;
}

double Drivetrain_Subsystem::getRightPost() 
{
    return m_right_front.get_position() / DrivetrainConstants::GEAR_REDUCTION;
}

bool Drivetrain_Subsystem::getExtension(){
    return isFlapsExtended; 
}

void Drivetrain_Subsystem::toggleExtension()
{
    isFlapsExtended = !isFlapsExtended;
    s_flaps_extension.set_value(isFlapsExtended);
}

void Drivetrain_Subsystem::setExtension(bool value)
{
    s_flaps_extension.set_value(value);
    isFlapsExtended = value;
}

void Drivetrain_Subsystem::joystickControl(pros::Controller controller) 
{
    mg_left.move(controller.get_analog(ANALOG_LEFT_Y));
    m_left_ext.move(controller.get_analog(ANALOG_LEFT_Y)); 
    mg_right.move(controller.get_analog(ANALOG_RIGHT_Y)); 
    m_right_ext.move(controller.get_analog(ANALOG_RIGHT_Y));
}

void Drivetrain_Subsystem::drivetrainControl(double leftPercent, double rightPercent)
{
    leftPercent *= 600;
    rightPercent *= 600;
    mg_left.move_velocity(leftPercent);
    m_left_ext.move_velocity(leftPercent);
    mg_right.move_velocity(rightPercent);
    m_right_ext.move_velocity(rightPercent);
}

void Drivetrain_Subsystem::stopControl()
{
    mg_left.brake();
    m_left_ext.brake();
    mg_right.brake();
    m_right_ext.brake();
}

void Drivetrain_Subsystem::printTask() 
{
    // pros::lcd::print(4, "LEFTMG: %f", m_left_rear.get_position());
	// pros::lcd::print(5, "RIGHTMG: %f", m_right_rear.get_position());
}

