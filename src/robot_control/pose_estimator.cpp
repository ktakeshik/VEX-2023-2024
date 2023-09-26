#include "pose_estimator.h"

Pose_Estimator ::Pose_Estimator ()
:   s_inertial(DrivetrainConstants::SP_INERTIAL),
    s_left_rotation(DrivetrainConstants::SP_LEFT_ROTATION),
    s_right_rotation(DrivetrainConstants::SP_RIGHT_ROTATION),
    previous_angle(0),
    previous_left_distance(0),
    previous_right_distance(0)
{
    zeroOutPosition();

    s_left_rotation.reset_position();
    s_right_rotation.reset_position();

    s_left_rotation.set_reversed(true);
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

double Pose_Estimator::getDistance(std::string s_rotation, double wheel_diameter)
{
    double temp {double( s_rotation == "left" ? s_left_rotation.get_position() : s_right_rotation.get_position())};
    return temp/36000 * 3/7 * (wheel_diameter * MiscConstants::PI);
}

double Pose_Estimator ::getInchesTraveled(pros::Rotation s_rotation, std::string string, double wheel_diameter) 
{
    double current_distance;
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

    current_distance = s_rotation.get_position();
    converted_distance = ((current_distance - previous_distance)/36000 * (wheel_diameter * MiscConstants::PI));
    
    if (string == "s_left_rotation")
    {
        previous_left_distance = current_distance;
    }
    else if (string == "s_right_rotation")
    {
        previous_right_distance = current_distance;
    }
    
    return converted_distance;
}

double Pose_Estimator ::distanceCalc() 
{   
    return (getDistance("left", DrivetrainConstants::LEFT_TRACKING_DIAMETER) 
        + getDistance("right", DrivetrainConstants::RIGHT_TRACKING_DIAMETER))/2;
}

void Pose_Estimator ::positionCalc()
{
    poseStruct.angle = s_inertial.get_heading() * (MiscConstants::PI/180);

    poseStruct.distance_traveled = distanceCalc();
    poseStruct.change_in_angle = poseStruct.angle - previous_angle;

    poseStruct.y_position = poseStruct.distance_traveled 
        * cos(poseStruct.angle + poseStruct.change_in_angle/2);
            
    poseStruct.x_position = poseStruct.distance_traveled 
        * sin(poseStruct.angle + poseStruct.change_in_angle/2);
    
    previous_angle = poseStruct.angle;
}

void Pose_Estimator ::setTarget(double x_position, double y_position)
{
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

bool Pose_Estimator::isRobotPastTarget()
{
    return (getDistanceToTarget() < 0) ? true : false;
}

bool Pose_Estimator::isXAxisAligned()
{
    return fabs(targetStruct.x_position - poseStruct.x_position) < 1 ? true : false;
}

bool Pose_Estimator::isYAxisAligned()
{
    return fabs(targetStruct.y_position - poseStruct.y_position) < 1 ? true : false;
}

double Pose_Estimator::getAngleToTarget()
{
    double orientation = -poseStruct.angle;
        
    double angleToTarget;

    float orientation_vector_x = 0 * cosf(orientation) - 1 * sinf(orientation);
    float orientation_vector_y = 1 * cosf(orientation) + 0 * sinf(orientation);

    double x_pos_relative = targetStruct.x_position - poseStruct.x_position;
    double y_pos_relative = targetStruct.y_position - poseStruct.y_position;

    if(isTargetAtOrigin() && isRobotAtOrigin())
    {
        return 0;
    }

    // if(poseStruct.angle > MiscConstants::PI)
    // {
    //     orientation = poseStruct.angle - (2 * MiscConstants::PI);
    // }

    angleToTarget = atan2(x_pos_relative, y_pos_relative) - atan2(orientation_vector_x, orientation_vector_y);

    if (rearToTarget()) 
    {
        angleToTarget = MiscConstants::PI + angleToTarget;
    }

    if(fabs(angleToTarget) > MiscConstants::PI)
    {
        angleToTarget -= copysignf((2 * MiscConstants::PI), angleToTarget);
    }

    return angleToTarget * (180/MiscConstants::PI);
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
    return poseStruct.angle * (180/MiscConstants::PI);
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
	// pros::lcd::print(2, "XPOSITION: %f", getXPosition());
	// pros::lcd::print(3, "YPOSITION: %f", getYPosition());
    pros::lcd::print(4, "ANGLE: %f", getAngleToTarget());
	pros::lcd::print(5, "DISTANCE: %f", getDistanceToTarget());
    pros::lcd::print(6, (rearToTarget() ? "BOOLEAN BOOLEAN: true" : "BOOLEAN BOOLEAN: false"));
}