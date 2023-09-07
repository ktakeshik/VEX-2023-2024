#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "main.h"

namespace Constants {

    const double PI = 3.14159265358979323846;

    namespace Drivetrain {
        //Motors
        const int MP_LEFT_FRONT = 16;
        const int MP_LEFT_REAR = 12;
        const int MP_LEFT_EXT = 11;
        const int MP_RIGHT_FRONT = 18;
        const int MP_RIGHT_REAR = 19;
        const int MP_RIGHT_EXT = 20;

        const bool M_LEFT_FRONT_REVERSED = true;
        const bool M_LEFT_REAR_REVERSED = true;
        const bool M_LEFT_EXT_REVERSED = false;
        const bool M_RIGHT_FRONT_REVERSED = true;
        const bool M_RIGHT_REAR_REVERSED = true;
        const bool M_RIGHT_EXT_REVERSED = true;

        const bool MG_LEFT_REVERSED = true;
        const bool MG_RIGHT_REVERSED = false;

        const pros::motor_brake_mode_e_t MG_LEFT_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
        const pros::motor_brake_mode_e_t MG_RIGHT_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

        //Sensors
        const char SP_FLAPS = 'A';

        const int SP_LEFT_ROTATION = 2;
        const int SP_RIGHT_ROTATION = 10;
        // const int SP_HORIZONTAL_ROTATION = 7;

        const bool S_LEFT_ROTATION_REVERSED = false;
        const bool S_RIGHT_ROTATION_REVERSED = true;
        // const bool S_HORIZONTAL_ROTATION_REVERSED = false;

        const int SP_INERTIAL = 8;

        //Measurements
        const double LEFT_TRACKING_DIAMETER = 4;
        const double RIGHT_TRACKING_DIAMETER = 4;
        // const double HORIZONTAL_TRACKING_DIAMETER = 3.25;

        const double CENTER_TO_LEFT = 5.8125;
        const double CENTER_TO_RIGHT = 5.8125;
        // const double CENTER_TO_HORIZONTAL = 10.5625;
        const double TRACKING_WHEELS_SPAN = 11.625;

        const double GEAR_REDUCTION = 2.33333333;
    }

    namespace Catapult {
        //Motors
        const int MP_CATAPULT = 4;
        const bool M_CATAPULT_REVERSED = false;
        const pros::motor_brake_mode_e_t M_CATAPULT_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;

        //Sensors
        const int SP_ROTATION = 6;
        const bool S_ROTATION_REVERSED = false;

        const float CATAPULT_MINIMUM_ANGLE = 30300;
        const float CATAPUL_MAXIMUM_ANGLE = 29074;

        const float CATAPULT_MID_MIN_ANGLE = 32000;
        const float CATAPUL_MID_MAX_ANGLE = 31000;

        const float CATAPULT_UP_ANGLE = 34000;
    }

    namespace Intake {
        const int MP_INTAKE = 1;
        const bool M_INTAKE_REVERSED = true;
        const pros::motor_brake_mode_e_t M_INTAKE_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;
        
        const char SP_INTAKE = 'B';
    }

    namespace Elevation {
        const char SP_ARM = 'C';
    }

    namespace Vision {
        const int SP_VISION = 16;

        const int IMAGE_WIDTH = 316;
        const int IMAGE_HEIGHT = 212;

        const double VERTICAL_FOV = 41;
        const double HORIZONTAL_FOV = 61;

        const double TRIBALL_DEPTH = 3.5;

        const double VISION_HEIGHT = 15.625;
        const double MOUNT_ANGLE = 55;

        const double GOAL_Y_MIN = 46;
        const double GOAL_Y_MAX = 98;
        const double GOAL_X_MIN = 0;
        const double GOAL_X_MAX = 24;

        const double RATIO_MIN = 0.8;
        const double RATIO_MAX = 1.3;
    }
}

#endif