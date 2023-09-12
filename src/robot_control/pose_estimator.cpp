#include "pose_estimator.h"

Pose_Estimator ::Pose_Estimator ()
:   s_inertial(Constants::Drivetrain::SP_INERTIAL),
    previous_angle(0),
    previous_left_distance(0),
    previous_right_distance(0)
{
    zeroOutPosition();
}

void Pose_Estimator::zeroOutPosition() 
{
    poseStruct.distance_traveled = 0;
    poseStruct.angle = 0;
    poseStruct.change_in_angle = 0;
    poseStruct.x_position = 0;
    poseStruct.y_position = 0;

    targetStruct.angle = 0;
    targetStruct.x_position = 0;
    targetStruct.y_position = 0;
}

double Pose_Estimator::getDistance(double position, double wheel_diameter)
{
   return position * (wheel_diameter * Constants::PI);
}

double Pose_Estimator ::getInchesTraveled(double position, std::string string, double wheel_diameter) 
{
    double previous_distance;
    double converted_distance;
    if (string == "s_left_rotation")
    {
        previous_distance = previous_left_distance;
    }
    else if (string == "s_right_rotation")
    {
        previous_distance = previous_right_distance;
    }

    converted_distance = ((position - previous_distance) * (wheel_diameter * Constants::PI));
    
    if (string == "s_left_rotation")
    {
        previous_left_distance = position;
    }
    else if (string == "s_right_rotation")
    {
        previous_right_distance = position;
    }
    
    return converted_distance;
}

double Pose_Estimator ::distanceCalc(double left_position, double right_position) 
{   
    return (getDistance(left_position, Constants::Drivetrain::LEFT_TRACKING_DIAMETER) 
        + getDistance(right_position, Constants::Drivetrain::RIGHT_TRACKING_DIAMETER))/2;
}

void Pose_Estimator ::positionCalc(double left_position, double right_position)
{
    poseStruct.angle = s_inertial.get_heading() * (Constants::PI/180);

    poseStruct.distance_traveled = distanceCalc(left_position, right_position);
    poseStruct.change_in_angle = poseStruct.angle - previous_angle;

    poseStruct.y_position = poseStruct.distance_traveled 
        * cos(poseStruct.angle + poseStruct.change_in_angle/2);
            
    poseStruct.x_position = poseStruct.distance_traveled 
        * sin(poseStruct.angle + poseStruct.change_in_angle/2);
    
    previous_angle = poseStruct.angle;
}

void Pose_Estimator ::setTarget(double orientation, double x_position, double y_position)
{
    targetStruct.angle = orientation;
    targetStruct.x_position = x_position;
    targetStruct.y_position = y_position;
}

bool Pose_Estimator ::rearToTarget(){
    return rear_to_target;
}

void Pose_Estimator ::setRearToTarget(bool value) {
    rear_to_target = value;
}

bool Pose_Estimator ::isRobotFacingTarget()
{
    return fabs(getAngleToTarget()) < 1 ? true : false;
}

bool Pose_Estimator ::isRobotAtTarget()
{
    return fabs(getDistanceToTarget()) < 1 ? true : false; 
}

bool Pose_Estimator ::isRobotAtOrigin()
{
    return poseStruct.x_position == 0 && poseStruct.y_position == 0 ? true : false;
}

bool Pose_Estimator ::isTargetAtOrigin()
{
    return targetStruct.x_position == 0 && targetStruct.y_position == 0 ? true : false;
}

double Pose_Estimator ::getAngleToTarget()
{
    double tempNum;
    double orientation = poseStruct.angle;
    double originToAngle;

    double x_pos_relative = targetStruct.x_position - poseStruct.x_position;
    double y_pos_relative = targetStruct.y_position - poseStruct.y_position;

    if(isTargetAtOrigin() && isRobotAtOrigin())
    {
        return 0;
    }
    else if(isTargetAtOrigin())
    {
        x_pos_relative = -poseStruct.x_position;
        y_pos_relative = -poseStruct.y_position;
    }

    if(poseStruct.angle > Constants::PI)
    {
        orientation = poseStruct.angle - (2 * Constants::PI);
    }

    if(y_pos_relative == 0)
    {
        tempNum = copysign(Constants::PI/2, x_pos_relative);
    }
    else if(x_pos_relative == 0)
    {
        tempNum = Constants::PI/2 + copysign(Constants::PI/2, y_pos_relative);
    }
    else
    {
        tempNum = atan(x_pos_relative/y_pos_relative);
    }

    if (rearToTarget() == true) 
    {
        if(y_pos_relative > 0 && x_pos_relative > 0)
        {
            tempNum -= Constants::PI;
        }
        else if(y_pos_relative > 0 && x_pos_relative < 0)
        {
            tempNum += Constants::PI;
        }
    }
    else 
    {
        if(y_pos_relative < 0 && x_pos_relative < 0)
        {
            tempNum -= Constants::PI;
        }
        else if(y_pos_relative < 0 && x_pos_relative > 0)
        {
            tempNum += Constants::PI;
        }
    }
    originToAngle = tempNum - orientation;

    if(fabs(originToAngle) >= (2 * Constants::PI))
    {
        originToAngle += copysign((2 * Constants::PI), originToAngle);
    }

    // if(fabs(originToAngle) > 180)
    // {
    //     originToAngle -= copysign((2 * Constants::PI), originToAngle);
    // }

    return originToAngle * (180/Constants::PI);
}

double Pose_Estimator ::getDistanceToTarget()
{
    double x_pos_relative {targetStruct.x_position - poseStruct.x_position};
    double y_pos_relative {targetStruct.y_position - poseStruct.y_position};
    double tempNum {sqrt(pow(x_pos_relative, 2) + pow(y_pos_relative, 2))};
    return (rearToTarget() == true) ? -tempNum : tempNum;
}

double Pose_Estimator ::getDistanceTraveled() 
{
    return poseStruct.distance_traveled;
}

double Pose_Estimator ::getOrientation()
{
    return poseStruct.angle * (180/Constants::PI);
}

double Pose_Estimator ::getXPosition()
{
    return poseStruct.x_position;
}

double Pose_Estimator ::getYPosition() 
{
    return poseStruct.y_position;
}

void Pose_Estimator ::printTask() 
{
    pros::lcd::print(1, "ORIENTATION: %f", getOrientation());
	pros::lcd::print(2, "XPOSITION: %f", getXPosition());
	pros::lcd::print(3, "YPOSITION: %f", getYPosition());
    pros::lcd::print(4, "ANGLE: %f", getAngleToTarget());
	pros::lcd::print(5, "DISTANCE: %f", getDistanceToTarget());
    pros::lcd::print(6, (rearToTarget() ? "BOOLEAN BOOLEAN: true" : "BOOLEAN BOOLEAN: false"));
}