#include "robot_control/auto_control.h"

void Autonomous_Control::setTarget(double x_pos, double y_pos, double orientation, bool value)
{
    pose_Estimator.setTarget(orientation, x_pos, y_pos);
    pose_Estimator.setRearToTarget(value);
}

void Autonomous_Control::setConstraints(double rotateMin, double rotateMax, double moveMin, double moveMax) 
{
    turnMin = rotateMin;
    turnMax = rotateMax;
    driveMin = moveMin;
    driveMax = moveMax;
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
        rotationController.setError(fabs(pose_Estimator.getAngleToTarget()));
        velocity = rotationController.getOutput();
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, pose_Estimator.getAngleToTarget());

        s_Drivetrain.drivetrainControl(velocity, -velocity);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::moveToTarget(double min, double max)
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
        accelerationController.setError(fabs(pose_Estimator.getDistanceToTarget()));
        velocity = accelerationController.getOutput();
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, pose_Estimator.getDistanceToTarget());

        rotationController.setError(pose_Estimator.getAngleToTarget());
        courseCorrection = rotationController.getOutput()/100 * velocity;
        courseCorrection = copysign(courseCorrection, rotationController.getError());

        s_Drivetrain.drivetrainControl(velocity + courseCorrection, velocity - courseCorrection);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::turnToAngle(double min, double max, double desiredAngle) 
{
    double angleToTarget;
    double velocity;

    do 
    {
        rotationController.setError(desiredAngle - pose_Estimator.getOrientation());
        velocity = rotationController.getOutput();
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, rotationController.getError());

        s_Drivetrain.drivetrainControl(velocity, -velocity);
        pros::delay(20);
    }
    while (rotationController.getError() > 1);

    s_Drivetrain.stopControl();
}

void Autonomous_Control::moveDistance(double min, double max, double desiredDistance)
{
    double distanceToTarget;
    double currentDistance{s_Drivetrain.getLeftPost()};
    double angleToTarget;
    double currentAngle{pose_Estimator.getOrientation()};
    double velocity;
    double courseCorrection;

    do 
    {
        accelerationController.setError((desiredDistance + currentDistance) - s_Drivetrain.getLeftPost());
        velocity = accelerationController.getOutput();
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, accelerationController.getError());

         rotationController.setError(pose_Estimator.getAngleToTarget());
        courseCorrection = rotationController.getOutput()/100 * velocity;
        courseCorrection = copysign(courseCorrection, rotationController.getError());

        s_Drivetrain.drivetrainControl(velocity + courseCorrection, velocity - courseCorrection);
        pros::delay(20);
    }
    while (accelerationController.getError() > 1);

    s_Drivetrain.stopControl();
}

void Autonomous_Control::setDrivetrain(float leftPercent, float rightPercent) 
{
    s_Drivetrain.drivetrainControl(leftPercent, rightPercent);
}

void Autonomous_Control::manueverToTarget(double x_pos, double y_pos, bool value) 
{
    setTarget(x_pos, y_pos, 0, value);
    turnToTarget(turnMin, turnMax);
    moveToTarget(driveMin, driveMax);
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
    pros::delay(800);
    s_Catapult.setCatapultState(Catapult_Subsystem::DEFAULT_STATE);
}

void Autonomous_Control::setCatapult(double value) 
{
    s_Catapult.setCatapultState(Catapult_Subsystem::STAY_UP);
    s_Catapult.setSaftey(true);
    s_Catapult.catapultControl(value);
}

void Autonomous_Control::setCatapultMid()
{
    s_Catapult.setCatapultState(Catapult_Subsystem::POSSESS_TRIBALL);
}

void Autonomous_Control::setCatapultDown()
{
    s_Catapult.setCatapultState(Catapult_Subsystem::DEFAULT_STATE);
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