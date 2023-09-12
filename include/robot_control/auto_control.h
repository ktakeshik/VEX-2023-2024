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

    float turnMin, turnMax, turnP, driveMin, driveMax, driveP;

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

    
    void setTarget(double x_pos, double y_pos, double orientation, bool value);

    void setConstraints(double turnMin, double turnMax, double turnP, double driveMin, double driveMax, double driveP);

    void turnToTarget(double min, double max, double turnP);

    void moveToTarget(double min, double max, double driveP);

    void turnToAngle(double min, double max, double turnP, double desiredAngle);

    void moveDistance(double min, double max, double driveP, double desiredDistance);

    void setDrivetrain(float leftPercent, float rightPercent);

    void manueverToTarget(double x_pos, double y_pos, bool value);

    void deployIntake(bool state);

    void setIntake(float percentOut);

    void launchCatapult();

    void setCatapultDown();

    void setCatapultMid();

    void setCatapult(double value);

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