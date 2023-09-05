#ifndef TELEOP_CONTROL_H
#define TELEOP_CONTROL_H
#include "main.h"
#include "Constants.h"
#include "subsystems/catapult_subsystem.h"
#include "subsystems/drivetrain_subsystem.h"
#include "subsystems/elevation_subsystem.h"
#include "subsystems/intake_subsystem.h"
#include "pose_estimator.h"


class Teleoperation_Control
{
    public:
    Teleoperation_Control(
        Catapult_Subsystem& catapult_Subsystem,
        Drivetrain_Subsystem& drivetrain_Subsystem,
        Elevation_Subsystem& elevation_Subsystem,
        Intake_Subsystem& intake_Subsystem
        ):
        s_Catapult(catapult_Subsystem),
        s_Drivetrain(drivetrain_Subsystem), 
        s_Elevation(elevation_Subsystem),
        s_Intake(intake_Subsystem){};

    void catapultControl();

    void teleopControl();

    void testCode();

    private:
    Catapult_Subsystem &s_Catapult;
    Drivetrain_Subsystem &s_Drivetrain;
    Elevation_Subsystem& s_Elevation;
    Intake_Subsystem& s_Intake;
};

#endif