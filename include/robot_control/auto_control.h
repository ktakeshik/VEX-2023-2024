#ifndef AUTO_CONTROL_H
#define AUTO_CONTROL_H
#include "main.h"
#include "Constants.h"
#include "subsystems/catapult_subsystem.h"
#include "subsystems/drivetrain_subsystem.h"
#include "subsystems/elevation_subsystem.h"
#include "subsystems/intake_subsystem.h"
#include "pose_estimator.h"
#include "pid_controller.h"

class Autonomous_Control
{
    private:

    PID_Controller rotationController;
    PID_Controller accelerationController;

    float maxAcceleration;
    float previousSpeed;

    public:

    float turnMin, turnMax, driveMin, driveMax;

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
        pose_Estimator(pose_Estimator){
        rotationController.setPGain(PIDConstants::K_ROTATION_P);
        rotationController.setIGain(PIDConstants::K_ROTATION_I);
        rotationController.setDGain(PIDConstants::K_ROTATION_D);
        rotationController.setFFGain(PIDConstants::K_ROTATION_FF);

        accelerationController.setPGain(PIDConstants::K_ACCELERATION_P);
        accelerationController.setIGain(PIDConstants::K_ACCELERATION_I);
        accelerationController.setDGain(PIDConstants::K_ACCELERATION_D);
        accelerationController.setFFGain(PIDConstants::K_ACCELERATION_FF);
    };
    
    void setTarget(double x_pos, double y_pos, double orientation, bool value);

    void setConstraints(double rotateMin, double rotateMax, double moveMin, double moveMax);

    void turnToTarget(double min, double max);

    void moveToTarget(double min, double max);

    void turnToAngle(double min, double max, double desiredAngle);

    void moveDistance(double min, double max, double desiredDistance);

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