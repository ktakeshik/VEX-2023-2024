#include "aSClib/command_scheduler.h"
#include "aSClib/controller_manager.h"
#include "aSClib/button_binding.h"
#include "aSClib/joystick_binding.h"

#include "subsystems/catapult_subsystem.h"
#include "subsystems/drivetrain_subsystem.h"
#include "subsystems/elevation_subsystem.h"
#include "subsystems/intake_subsystem.h"
#include "robot_control/pose_estimator.h"

#include "commands/Intake/toggleIntakeCommand.h"
#include "commands/Intake/powerIntakeCommand.h"

class Robot_Container {
    private:
    Command_Scheduler scheduler;
    Controller_Manager manager;

    Catapult_Subsystem s_Catapult;
    Drivetrain_Subsystem s_Drivetrain;
    Elevation_Subsystem s_Elevation;
    Intake_Subsystem s_Intake;
    Pose_Estimator s_Pose;

    toggleIntakeCommand toggleIntake = toggleIntakeCommand(&s_Intake);
    // powerIntakeCommand intakeControl = powerIntakeCommand(&s_Intake);


    public:

    Robot_Container() {
        configureBindings();

        scheduler
        .assignSubsystem(&s_Intake);
        // .scheduleDefaultCommand(&intakeControl);
    }

    void configureBindings() {
        pros::Controller master(pros::E_CONTROLLER_MASTER);

        Button_Binding toggleIntakeHandler = Button_Binding(&scheduler, master, pros::E_CONTROLLER_DIGITAL_L1)
            .onTrue(
                &toggleIntake
            );
        manager.addBinding(&toggleIntakeHandler);


    }

    void testLoop(pros::Controller controller) {
        // if (controller.get_digital_new_press(DIGITAL_L2)) {
        //     scheduler.addCommand(&intakeCommand);
        //     pros::lcd::print(5, "RIGHTMG: %f", i);
        //     i += 1;
        // }
    }

    void run() {
        manager.run();
        scheduler.run();
    }

    void shutdown() {scheduler.shutdown();} 

};