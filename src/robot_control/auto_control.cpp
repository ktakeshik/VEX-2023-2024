#include "robot_control/auto_control.h"

void Autonomous_Control::setTarget(double x_pos, double y_pos, double orientation, bool value)
{
    pose_Estimator.setTarget(orientation, x_pos, y_pos);
    pose_Estimator.setRearToTarget(value);
}

void Autonomous_Control::setConstraints(double rotateMin, double rotateMax, double rotateP, double moveMin, double moveMax, double moveP) {
    turnMin = rotateMin;
    turnMax = rotateMax;
    turnP = rotateP;
    driveMin = moveMin;
    driveMax = moveMax;
    driveP = moveP;
}

void Autonomous_Control::turnToTarget(double min, double max, double turnP)
{
    double angleToTarget;
    double velocity;
    pros::lcd::print(7, "AAAAAAAAAAAAAAAAAA");
    if(pose_Estimator.isRobotFacingTarget())
    {
        return;
    }

    while(!pose_Estimator.isRobotFacingTarget())
    {
        angleToTarget = pose_Estimator.getAngleToTarget();
        velocity = angleToTarget * turnP;
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, angleToTarget);

        s_Drivetrain.drivetrainControl(velocity, -velocity);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::moveToTarget(double min, double max, double driveP)
{
    double distanceToTarget;
    double angleToTarget;
    double velocity;
    double courseCorrection;

    if(pose_Estimator.isRobotAtTarget())
    {
        return;
    }

    while(!pose_Estimator.isRobotAtTarget())
    {
        angleToTarget = pose_Estimator.getAngleToTarget();
        distanceToTarget = pose_Estimator.getDistanceToTarget();
        velocity = distanceToTarget * driveP;
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, distanceToTarget);

        courseCorrection = angleToTarget/100 * velocity;
        courseCorrection = copysign(courseCorrection, angleToTarget);

        s_Drivetrain.drivetrainControl(velocity + courseCorrection, velocity - courseCorrection);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::manueverToTarget(double x_pos, double y_pos, bool value) {
    setTarget(x_pos, y_pos, 0, true);
    turnToTarget(turnMin, turnMax, turnP);
    moveToTarget(driveMin, driveMax, driveP);
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
    pros::delay(100);
    s_Catapult.setCatapultState(Catapult_Subsystem::DEFAULT_STATE);
}

void Autonomous_Control::setCatapultMid()
{
    s_Catapult.setCatapultState(Catapult_Subsystem::POSSESS_TRIBALL);
}

void Autonomous_Control::deployElevation(bool state)
{
    s_Elevation.setExtension(state);
}

void Autonomous_Control::testCode()
{
    // turnToTarget(0, 100);
    // moveToTarget(0, 100);
}