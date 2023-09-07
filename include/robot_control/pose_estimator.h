#ifndef POSE_ESTIMATOR_H
#define POSE_ESTIMATOR_H
#include "main.h"
#include "Constants.h"

class Pose_Estimator {
    private:

    //Sensors
    // pros::Rotation s_left_rotation;
	// pros::Rotation s_right_rotation;
    pros::Imu s_inertial;

    //Odometry
    struct Robot_Pose 
    {
        double distance_traveled, angle, change_in_angle, x_position, y_position;
    };

    struct Target_Pose
    {
        double angle, x_position, y_position;
    };

    Robot_Pose poseStruct;
    Target_Pose targetStruct;

    double distance_traveled;
    double angle_difference;
    double previous_angle;
    double previous_left_distance;
    double previous_right_distance;
    bool rear_to_target;

    public:
    //Constructor
    Pose_Estimator();

    //Methods
    double getDistance(double position, double wheel_diameter);

    double getInchesTraveled(double position, std::string string, double wheel_diameter);

    double angleCalc(double left_position, double right_position);

    double distanceCalc(double left_position, double right_position);

    void positionCalc(double left_position, double right_position);

    void setTarget(double orientation, double x_position, double y_position);

    bool rearToTarget();

    void setRearToTarget(bool value);

    bool isRobotFacingTarget();

    bool isRobotAtTarget();

    bool isRobotAtOrigin();

    bool isTargetAtOrigin();

    double getAngleToTarget();

    double getDistanceToTarget();

    double getDistanceTraveled();

    double getOrientation();

    double getXPosition();

    double getYPosition();

    void printTask();

};

#endif