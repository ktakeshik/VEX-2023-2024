#include "robot_control/auto_control.h"

void Autonomous_Control::setTarget(double x_pos, double y_pos, double orientation)
{
    pose_Estimator.setTarget(orientation, x_pos, y_pos);
}

void Autonomous_Control::turnToTarget(double min, double max)
{
    double angleToTarget;
    double velocity;

    if(pose_Estimator.isRobotFacingTarget())
    {
        return;
    }

    while(!pose_Estimator.isRobotFacingTarget())
    {
        angleToTarget = pose_Estimator.getAngleToTarget();
        velocity = (angleToTarget/3 < min) ? min : ((angleToTarget/3 > max) ? max : angleToTarget/3);
        velocity = copysign(velocity, angleToTarget);
        velocity /= 100;

        s_Drivetrain.drivetrainControl(velocity, -velocity);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::moveToTarget(double min, double max)
{
    double distanceToTarget;
    double velocity;
    double courseCorrection;

    if(pose_Estimator.isRobotAtTarget())
    {
        return;
    }

    while(!pose_Estimator.isRobotAtTarget())
    {
        distanceToTarget = pose_Estimator.getDistanceToTarget();
        velocity = (distanceToTarget/0.5 < min) ? min : ((distanceToTarget/0.5 > max) ? max : distanceToTarget/0.5);
        velocity = copysign(velocity, distanceToTarget);
        velocity /= 100;

        courseCorrection = pose_Estimator.getAngleToTarget()/200;

        s_Drivetrain.drivetrainControl(velocity + courseCorrection, velocity - courseCorrection);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::deployIntake(bool state)
{
    s_Intake.setExtension(state);
}

void Autonomous_Control::setIntake(float percentOut)
{
    s_Intake.intakeControl(percentOut);
}

void Autonomous_Control::launchCatapult()
{
    s_Catapult.setCatapultState(Catapult_Subsystem::LAUNCH_TRIBALL);
}

void Autonomous_Control::deployElevation(bool state)
{
    s_Elevation.setExtension(state);
}

void Autonomous_Control::testCode()
{
    setTarget(0, -3, 0);
    // turnToTarget(0, 100);
    // moveToTarget(0, 100);
}