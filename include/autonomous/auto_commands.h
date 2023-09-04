#ifndef AUTO_COMMANDS_H
#define AUTO_COMMANDS_H
#include "main.h"
#include "Constants.h"

#include "subsystems/drivetrain_subsystem.h"
#include "subsystems/intake_subsystem.h"
#include "subsystems/catapult_subsystem.h"
#include "subsystems/elevation_subsystem.h"

class Auto_Commands {
    private:
    Drivetrain_Subsystem s_Drive;
    Intake_Subsystem s_Intake;
    Catapult_Subsystem s_Catapult;
    Elevation_Subsystem s_Elevation;

    public:
    Auto_Commands(Drivetrain_Subsystem s_Drive, Intake_Subsystem s_Intake, 
        Catapult_Subsystem s_Catapult, Elevation_Subsystem s_Elevation);


    void printTask();
};

#endif