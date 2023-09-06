#ifndef AUTO_CONTROL_H
#define AUTO_CONTROL_H
#include "main.h"
#include "Constants.h"
#include "subsystems/catapult_subsystem.h"
#include "subsystems/drivetrain_subsystem.h"
#include "subsystems/elevation_subsystem.h"
#include "subsystems/intake_subsystem.h"
#include "pose_estimator.h"

class Autonomous_Control
{
    public:
    Autonomous_Control(
        Catapult_Subsystem& catapult_Subsystem,
        Drivetrain_Subsystem& drivetrain_Subsystem,
        Elevation_Subsystem& elevation_Subsystem,
        Intake_Subsystem& intake_Subsystem, 
        Pose_Estimator& pose_Estimator
        ):
        s_Catapult(catapult_Subsystem),
        s_Drivetrain(drivetrain_Subsystem), 
        s_Elevation(elevation_Subsystem),
        s_Intake(intake_Subsystem),
        pose_Estimator(pose_Estimator){};

    void setTarget(double x_pos, double y_pos, double orientation);

    void turnToTarget(double min, double max);

    void moveToTarget(double min, double max);

    void deployIntake(bool state);

    void setIntake(float percentOut);

    void launchCatapult();

    void deployElevation(bool state);

    void testCode();

    private:
    Catapult_Subsystem &s_Catapult;
    Drivetrain_Subsystem &s_Drivetrain;
    Elevation_Subsystem& s_Elevation;
    Intake_Subsystem& s_Intake;
    Pose_Estimator &pose_Estimator;
};

#endif