#include "main.h"
#include "subsystems\catapult_subsystem.h"
#include "subsystems\drivetrain_subsystem.h"
#include "subsystems\elevation_subsystem.h"
#include "subsystems\intake_subsystem.h"


Catapult_Subsystem s_Catapult;
Drivetrain_Subsystem s_Drivetrain;
Elevation_Subsystem s_Elevation;
Intake_Subsystem s_Intake;
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	
	pros::Task printTask{[] {
		while(true)
		{
			s_Catapult.printTask();
			pros::delay(20);
		}
	}};
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Task teleOp{[] {
		pros::Controller master(pros::E_CONTROLLER_MASTER);
		while(true)
		{
			s_Catapult.catapultControl(master, s_Intake.getExtensionStatus());
			// if (master.get_digital(DIGITAL_R1)) {
			// 	s_Catapult.autoCatapultMovement(master, s_Intake.getExtensionStatus());
			// }
			s_Drivetrain.joystickControl(master);
			s_Drivetrain.flapsControl(master);
			s_Elevation.elevationControl(master);
			s_Intake.intakeControl(master);
			s_Intake.intakeExtensionControl(master);
			pros::delay(20);
		}
	}};
}
