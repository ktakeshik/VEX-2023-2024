#ifndef POWER_INTAKE_COMMAND_H
#define POWER_INTAKE_COMMAND_H
#include "aSClib\command_base.h"

#include "main.h"
#include "subsystems\intake_subsystem.h"

class powerIntakeCommand : virtual public Command_Base {
    public:

    powerIntakeCommand(Intake_Subsystem* intake_Subsystem): s_Intake(intake_Subsystem) {
        addRequirement(s_Intake);
    };

    void execute() override;

    bool isFinished() override;

    private:
    Intake_Subsystem* s_Intake;
    bool intialIntakeState;
};
#endif