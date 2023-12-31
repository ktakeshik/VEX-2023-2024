#include "catapult_subsystem.h"

Catapult_Subsystem::Catapult_Subsystem ()
:   m_catapult(CatapultConstants::MP_CATAPULT),
    s_rotation(CatapultConstants::SP_ROTATION)
{
    //Motor Configuration & Intialization
    pros::Motor m_catapult_configurator(CatapultConstants::MP_CATAPULT,
        MOTOR_GEARSET_06, CatapultConstants::M_CATAPULT_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);
    
    m_catapult_configurator.set_brake_mode(CatapultConstants::M_CATAPULT_BRAKE_MODE);

    s_rotation.set_reversed(CatapultConstants::S_ROTATION_REVERSED);

    setCatapultState(Catapult_Subsystem::STAY_UP);
    setSaftey(true);
}

bool Catapult_Subsystem::isCatapultDown() 
{
    return (s_rotation.get_angle() < CatapultConstants::CATAPULT_MINIMUM_ANGLE &&
        s_rotation.get_angle() > CatapultConstants::CATAPUL_MAXIMUM_ANGLE) ?
        true : false;
}

bool Catapult_Subsystem::isCatapultMiddle() 
{
    return (s_rotation.get_angle() < CatapultConstants::CATAPULT_MID_MIN_ANGLE &&
        s_rotation.get_angle() > CatapultConstants::CATAPUL_MID_MAX_ANGLE) ?
        true : false;
}

bool Catapult_Subsystem::isCatapultUp() 
{
    return (s_rotation.get_angle() > CatapultConstants::CATAPULT_UP_ANGLE) ?
        true : false;
}

void Catapult_Subsystem::setSaftey(bool value) 
{
    saftey = value;
}

void Catapult_Subsystem::toggleSaftey() 
{
    saftey = !saftey;
}

bool Catapult_Subsystem::getSaftey() 
{
    return saftey;
}

void Catapult_Subsystem::setCatapultState(catapult_state status) 
{
    cata_status = status;
}

int Catapult_Subsystem::getCatapultState() 
{
    return cata_status;
}

void Catapult_Subsystem::catapultControl(float percentOut) 
{
    percentOut *= 600;
    m_catapult.move_velocity(fabsf(percentOut));
}

void Catapult_Subsystem::stopCatapult() 
{
    m_catapult.brake();
}

void Catapult_Subsystem::printTask() 
{
	// pros::lcd::print(2, "RIGHTMG: %f", m_right_rear.get_actual_velocity());
}

