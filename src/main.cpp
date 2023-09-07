#include "main.h"
#include "subsystems/catapult_subsystem.h"
#include "subsystems/drivetrain_subsystem.h"
#include "subsystems/elevation_subsystem.h"
#include "subsystems/intake_subsystem.h"
#include "robot_control/auto_control.h"
#include "robot_control/auto_paths.h"
#include "robot_control/pose_estimator.h"
#include "robot_control/teleop_control.h"

Catapult_Subsystem s_Catapult;
Drivetrain_Subsystem s_Drivetrain;
Elevation_Subsystem s_Elevation;
Intake_Subsystem s_Intake;
Pose_Estimator s_Pose;

Autonomous_Control s_AutoControl = Autonomous_Control(s_Catapult, s_Drivetrain, s_Elevation, s_Intake, s_Pose);
Autonomous_Paths r_Auto = Autonomous_Paths(s_AutoControl);

Teleoperation_Control r_Teleop = Teleoperation_Control(s_Catapult, s_Drivetrain, s_Elevation, s_Intake);
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
			s_Drivetrain.printTask();
			s_Elevation.printTask();
			s_Intake.printTask();
			s_Pose.printTask();
			pros::delay(20);
		}
	}};

	pros::Task poseTask{[] {
		while(true)
		{
			s_Pose.positionCalc(s_Drivetrain.getLeftPost(), s_Drivetrain.getRightPost());
			pros::delay(5);
		}
	}};

	pros::Task catapultTask{[] {
		while(true)
		{
			r_Teleop.catapultControl();
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
void autonomous() {
	r_Auto.setAutoPath(Autonomous_Paths::RIGHT_PATH);
	

	switch (r_Auto.getAutoPath()) {
		case Autonomous_Paths::NONE:
		break;
		
		case Autonomous_Paths::TESTING:
		r_Auto.test();
		break;

		case Autonomous_Paths::LEFT_PATH:
		r_Auto.leftPath();
		break;

		case Autonomous_Paths::RIGHT_PATH:
		r_Auto.rightPath();
		break;

		case Autonomous_Paths::SKILLS_PATH:
		r_Auto.skillsPath();
		break;
	}
}

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
		r_Teleop.teleopControl();
	}};
}
