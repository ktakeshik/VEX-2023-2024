#include "commands/Intake/powerIntakeCommand.h"

void powerIntakeCommand::execute() {
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    if (master.get_digital(OperatorConstants::INTAKE_FORWARD)) {
        s_Intake->intakeControl(1);
    }
    else if (master.get_digital(OperatorConstants::INTAKE_REVERSE)) {
        s_Intake->intakeControl(-1);
    }
    else {
        s_Intake->intakeControl(0);
    }
}

bool powerIntakeCommand::isFinished() {
    return false;
}