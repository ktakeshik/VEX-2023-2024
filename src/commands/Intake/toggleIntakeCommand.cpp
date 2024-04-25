#include "commands/Intake/toggleIntakeCommand.h"

void toggleIntakeCommand::initialize() {
    intialIntakeState = {s_Intake->getExtension()};
}

void toggleIntakeCommand::execute() {
    s_Intake->toggleExtension();
}

bool toggleIntakeCommand::isFinished() {
    return s_Intake->getExtension() != intialIntakeState;
}