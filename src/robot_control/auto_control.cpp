#include "robot_control/auto_control.h"

void Autonomous_Control::setTarget(double x_pos, double y_pos, bool value)
{
    pose_Estimator.setTarget(x_pos, y_pos);
    pose_Estimator.setRearToTarget(value);
}

void Autonomous_Control::setRequirement(endRequirement value)
{
    requirement = value;
}

bool Autonomous_Control::getRequirementStatus()
{
    switch(requirement) 
    {
        case endRequirement::fullStop:
            return !pose_Estimator.isRobotAtTarget();
            break;

        case endRequirement::alignXAxis:
            return !pose_Estimator.isXAxisAligned();
            break;
        
        case endRequirement::alignYAxis:
            return !pose_Estimator.isYAxisAligned();
            break;
        
        case endRequirement::pastPoint:
            return !pose_Estimator.isRobotPastTarget();
            break;

        default:
            return false;
            break;
    }
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

    rotationController.resetController();
    
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

    accelerationControllerL.resetController();

    if(pose_Estimator.isRobotAtTarget())
    {
        return;
    }

    do
    {
        accelerationControllerL.setError(fabs(pose_Estimator.getDistanceToTarget()));
        velocity = accelerationControllerL.getOutput();
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, pose_Estimator.getDistanceToTarget());

        rotationController.setError(pose_Estimator.getAngleToTarget());
        courseCorrection = rotationController.getOutput()/100 * velocity;
        courseCorrection = copysign(courseCorrection, rotationController.getError());

        s_Drivetrain.drivetrainControl(velocity + courseCorrection, velocity - courseCorrection);
        pros::delay(20);
    }
    while (getRequirementStatus());

    s_Drivetrain.stopControl();
}

void Autonomous_Control::turnToAngle(double min, double max, double desiredAngle) 
{
    double angleToTarget;
    double velocity;
    double error = desiredAngle - pose_Estimator.getOrientation();

    while (fabs(error) > 1)
    {
        error = desiredAngle - pose_Estimator.getOrientation();
        rotationController.setError(fabs(error) < 180 ? error : error - copysign((360), error));
        velocity = rotationController.getOutput();
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, rotationController.getError());

        s_Drivetrain.drivetrainControl(velocity, -velocity);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::moveDistance(double min, double max, double desiredDistance)
{
    double distanceToTarget;
    double currentDistance{s_Drivetrain.getLeftPost()};
    double startingLeftPos{pose_Estimator.getDistance("left", 4)};
    double startingRightPos{pose_Estimator.getDistance("right", 4)};
    double angleToTarget;
    double currentAngle{pose_Estimator.getOrientation()};
    double velocityLeft;
    double velocityRight;
    double courseCorrection;

    do 
    {
        accelerationControllerL.setError((desiredDistance + startingLeftPos) - pose_Estimator.getDistance("left", 4));
        velocityLeft = accelerationControllerL.getOutput();
        velocityLeft /= 100;
        velocityLeft = (velocityLeft < min) ? min : ((velocityLeft > max) ? max : velocityLeft);
        velocityLeft = copysign(velocityLeft, accelerationControllerL.getError());

        accelerationControllerR.setError((desiredDistance + startingRightPos) - pose_Estimator.getDistance("right", 4));
        velocityRight = accelerationControllerL.getOutput();
        velocityRight /= 100;
        velocityRight = (velocityRight < min) ? min : ((velocityRight > max) ? max : velocityRight);
        velocityRight = copysign(velocityRight, accelerationControllerL.getError());

        rotationController.setError(pose_Estimator.getAngleToTarget());
        courseCorrection = rotationController.getOutput()/100 * (velocityLeft + velocityRight)/2;
        courseCorrection = copysign(courseCorrection, rotationController.getError());

        s_Drivetrain.drivetrainControl(velocityLeft + courseCorrection, velocityRight - courseCorrection);
        pros::delay(20);
        pros::lcd::print(2, "DESIRED_ANGLE: %f", accelerationControllerL.getError());
        pros::lcd::print(2, "DESIRED_ANGLE: %f", accelerationControllerR.getError());
    }
    while (fabs(accelerationControllerL.getError()) > 1 && fabs(accelerationControllerR.getError()) > 1);

    s_Drivetrain.stopControl();
}

void Autonomous_Control::setDrivetrain(float leftPercent, float rightPercent) 
{
    s_Drivetrain.drivetrainControl(leftPercent, rightPercent);
}

void Autonomous_Control::manueverToTarget(bool rotate, bool move) 
{
    if (rotate) {
        turnToTarget(turnMin, turnMax);
    }
    if (move) {
        moveToTarget(driveMin, driveMax);
    }
}

void Autonomous_Control::deployIntake(bool state)
{
    s_Intake.setExtension(state);
}

void Autonomous_Control::deployExtension(bool state) 
{
    s_Drivetrain.setExtension(state);
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

void Autonomous_Control::setCatapultUp()
{
    s_Catapult.setCatapultState(Catapult_Subsystem::LAUNCH_TRIBALL);
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