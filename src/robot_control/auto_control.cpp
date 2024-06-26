#include "robot_control/auto_control.h"

void Autonomous_Control::startTimer(double timeStarted) {
    this->timeStarted = timeStarted;
}

double Autonomous_Control::getTimeSeconds() {
    return (pros::c::millis() - timeStarted)/100;
}

double Autonomous_Control::getTimeMilliseconds() {
    return pros::c::millis() - timeStarted;
}

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

void Autonomous_Control::turnToHeading(double min, double max, double desiredAngle)
{
    double velocity;
    double error = desiredAngle - pose_Estimator.getHeading();

    while (fabs(error) > 1)
    {
        error = desiredAngle - pose_Estimator.getHeading();
        error = fabs(error) > 180 ? error - copysign(360, error) : error;
        rotationController.setError(fabs(error));
        velocity = rotationController.getOutput();
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, error);
        pros::lcd::print(2, "RIGHTMG: %f", error);
        pros::lcd::print(3, "RIGHTMG: %f", velocity);

        s_Drivetrain.drivetrainControl(velocity, -velocity);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::turnToAngle(double min, double max, double desiredAngle) 
{
    double velocity;
    double target = pose_Estimator.getOrientation() + desiredAngle;
    double error = target - pose_Estimator.getOrientation();

    while (fabs(error) > 1)
    {
        error = target - pose_Estimator.getOrientation();
        rotationController.setError(fabs(error));
        velocity = rotationController.getOutput();
        velocity /= 100;
        velocity = (velocity < min) ? min : ((velocity > max) ? max : velocity);
        velocity = copysign(velocity, error);

        s_Drivetrain.drivetrainControl(velocity, -velocity);
        pros::delay(20);
    }

    s_Drivetrain.stopControl();
}

void Autonomous_Control::moveDistance(double min, double max, double desiredDistance)
{
    double currentDistance{s_Drivetrain.getLeftPost()};
    double desiredLeftPos{desiredDistance + pose_Estimator.getDistance("left", 4)};
    double desiredRightPos{desiredDistance + pose_Estimator.getDistance("right", 4)};
    double leftPosError{desiredLeftPos - pose_Estimator.getDistance("left", 4)};
    double rightPosError{desiredRightPos - pose_Estimator.getDistance("right", 4)};
    double velocityLeft;
    double velocityRight;
    double courseCorrection;

    do 
    {
        leftPosError = {desiredLeftPos - pose_Estimator.getDistance("left", 4)};
        rightPosError = {desiredRightPos - pose_Estimator.getDistance("right", 4)};

        accelerationControllerL.setError(fabs(leftPosError));
        velocityLeft = accelerationControllerL.getOutput();
        velocityLeft /= 100;
        velocityLeft = (velocityLeft < min) ? min : ((velocityLeft > max) ? max : velocityLeft);
        velocityLeft = copysign(velocityLeft, leftPosError);

        accelerationControllerR.setError(fabs(rightPosError));
        velocityRight = accelerationControllerR.getOutput();
        velocityRight /= 100;
        velocityRight = (velocityRight < min) ? min : ((velocityRight > max) ? max : velocityRight);
        velocityRight = copysign(velocityRight, rightPosError);

        s_Drivetrain.drivetrainControl(velocityLeft, velocityRight);
    }
    while (fabs(leftPosError) > 1 && fabs(rightPosError) > 1);

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