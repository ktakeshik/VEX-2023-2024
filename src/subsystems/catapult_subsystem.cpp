#include "catapult_subsystem.h"

using namespace Constants::Catapult;

Catapult_Subsystem::Catapult_Subsystem ()
:   m_catapult(MP_CATAPULT),
    s_rotation(SP_ROTATION)
{
    //Motor Configuration & Intialization
    pros::Motor m_catapult_configurator(MP_CATAPULT,
        MOTOR_GEARSET_06, M_CATAPULT_REVERSED, 
        MOTOR_ENCODER_ROTATIONS);
    
    m_catapult_configurator.set_brake_mode(M_CATAPULT_BRAKE_MODE);

    s_rotation.set_reversed(S_ROTATION_REVERSED);
}

bool Catapult_Subsystem::isCatapultDown() {
    return (s_rotation.get_angle() < CATAPULT_MINIMUM_ANGLE &&
        s_rotation.get_angle() > CATAPUL_MAXIMUM_ANGLE) ?
        true : false;
}

bool Catapult_Subsystem::isCatapultUp() {
    return (s_rotation.get_angle() > CATAPULT_UP_ANGLE) ?
        true : false;
}

void Catapult_Subsystem::catapultControl(pros::Controller controller, bool intakeOut) {
    if (!intakeOut) {
        return;
    }
    if (controller.get_digital(DIGITAL_R1)) {
        m_catapult.move(60);
        return;
    }
    m_catapult.brake();
}

void Catapult_Subsystem::autoCatapultMovement(bool intakeOut) {
    if (!intakeOut) {
        return;
    }

    if (!isCatapultUp()) {
        m_catapult.move(127);
        pros::delay(20);  
    }
    else {
        m_catapult.brake();
    }
}

void Catapult_Subsystem::loadCatapult(bool intakeOut) {
    if (!intakeOut) {
        return;
    }
    
    if (!isCatapultDown()) {
        m_catapult.move(110);
        pros::delay(20);
    }
    else {
        m_catapult.brake();
    }
}

void Catapult_Subsystem::continuosShoot(bool intakeOut, pros::Controller controller) {
    if (!intakeOut) {
        return;
    }

    if (controller.get_digital(DIGITAL_R2)) {

        m_catapult.move(127);

        // while(!isCatapultDown()) {
        //     m_catapult.move(110);
        //     pros::delay(20);
        // }
        // m_catapult.brake();

        // pros::delay(0);

        // while(!isCatapultUp()) {
        //     m_catapult.move(127);
        //     pros::delay(20);  
        // }
    }
    else {
        m_catapult.brake();
    }
}

void Catapult_Subsystem::printTask() 
{
    pros::lcd::print(2, "LEFTMG: %i", s_rotation.get_angle());
	// pros::lcd::print(2, "RIGHTMG: %f", m_right_rear.get_actual_velocity());
}

