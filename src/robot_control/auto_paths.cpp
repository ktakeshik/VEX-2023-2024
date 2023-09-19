#include "auto_paths.h"
#include "auto_control.h"

void Autonomous_Paths::test() 
{
    r_Auto.setConstraints(0.05, 1, 0.05, 1);
    r_Auto.manueverToTarget(24, 12, true);
}

void Autonomous_Paths::leftPath() 
{
    r_Auto.setConstraints(0.05, 0.6, 0.4, 1.5);
    r_Auto.manueverToTarget(8, -20, true);
    r_Auto.setDrivetrain(-0.7, -0.7);
    pros::delay(250);
    r_Auto.setDrivetrain(0.3, 0.3);
    r_Auto.deployIntake(true);
    r_Auto.setIntake(1);
    pros::delay(350);
    r_Auto.setDrivetrain(-0.5,0.5);
    pros::delay(115);
    r_Auto.setDrivetrain(0.5,0.5);
    pros::delay(600);
    r_Auto.setDrivetrain(0,0);
    pros::delay(100);
    r_Auto.setDrivetrain(0.5,-0.5);
    r_Auto.setCatapultDown();
    pros::delay(400);
    r_Auto.setDrivetrain(0.5,0.5);
    pros::delay(500);
    r_Auto.setDrivetrain(0,0);
    pros::delay(2000);
    r_Auto.launchCatapult();
    r_Auto.setIntake(0);
    // r_Auto.setDrivetrain(0.5,-0.5);
    // pros::delay(500);
    // r_Auto.setConstraints(0.05, 0.6, 0.9, 0.4, 1, 1.5);
    // r_Auto.manueverToTarget(30, -20, true);

}

void Autonomous_Paths::rightPath() 
{
    r_Auto.setConstraints(0.05, 0.6, 0.4, 1.5);
    r_Auto.manueverToTarget(-10, -20, true);
    r_Auto.setDrivetrain(-0.5, -0.5);
    pros::delay(250);
    r_Auto.setDrivetrain(0.3, 0.3);
    pros::delay(700);
    r_Auto.setConstraints(0.05, 0.6, 0.25, 1.5);
    r_Auto.manueverToTarget(15, -4, false);
    r_Auto.deployIntake(true);
    r_Auto.setCatapultMid();
    r_Auto.setDrivetrain(0.4, 0.4);
    r_Auto.setIntake(1);
    pros::delay(500);
    r_Auto.setDrivetrain(0, 0);
    pros::delay(250);
    r_Auto.setIntake(0);
    r_Auto.setDrivetrain(-0.2, 0.2);
    pros::delay(700);
    r_Auto.setDrivetrain(0.2, 0.2);
    pros::delay(1000);
    r_Auto.setDrivetrain(0, 0);
    
}

void Autonomous_Paths::skillsPath() 
{
    r_Auto.setConstraints(0.05, 1, 0.05, 1);
    r_Auto.manueverToTarget(18, 12, true);
}

void Autonomous_Paths::setAutoPath(auto_path desiredPath) 
{
    paths = desiredPath;
}

int Autonomous_Paths::getAutoPath() 
{
    return paths;
}

void Autonomous_Paths::printTask() 
{
    
}