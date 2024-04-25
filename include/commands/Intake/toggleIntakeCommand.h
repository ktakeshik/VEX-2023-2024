#ifndef TOGGLE_INTAKE_COMMAND_H
#define TOGGLE_INTAKE_COMMAND_H
#include "aSClib\command_base.h"
#include "subsystems\intake_subsystem.h"

class toggleIntakeCommand : virtual public Command_Base {
    public:

    toggleIntakeCommand(Intake_Subsystem* intake_Subsystem): s_Intake(intake_Subsystem){
        addRequirement(s_Intake);
    };

    void initialize() override;

    void execute() override;

    bool isFinished() override;

    private:
    Intake_Subsystem* s_Intake;
    bool intialIntakeState;
};
#endif