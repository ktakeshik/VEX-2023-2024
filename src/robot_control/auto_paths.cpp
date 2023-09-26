#include "auto_paths.h"
#include "auto_control.h"

void Autonomous_Paths::test() 
{
    r_Auto.turnToAngle(0.05, 1, 90);
    // r_Auto.moveDistance(0.05, 0.5, 12);
    // // r_Auto.setConstraints(0.01, 0.3, 0.05, 0.4);
    // // r_Auto.setTarget(4, 4, true);
    // // r_Auto.manueverToTarget(true, true);
    // // r_Auto.setConstraints(0.01, 0.2, 0.05, 0.4);
    // // r_Auto.setTarget(-4, -4, true);
    // // r_Auto.manueverToTarget(true, true);
}

void Autonomous_Paths::leftPath() 
{
    r_Auto.setConstraints(0.01, 0.6, 0.4, 1.5);
    r_Auto.setTarget(8, -16, true);
    r_Auto.manueverToTarget(true, true);
    r_Auto.setConstraints(0.05, 0.4, 0.05, 1);
    r_Auto.setTarget(8, -100, true);
    r_Auto.manueverToTarget(true, false);
    r_Auto.setDrivetrain(-0.7, -0.7);
    pros::delay(250);
    r_Auto.setDrivetrain(0.3, 0.3);
    r_Auto.deployIntake(true);
    r_Auto.setIntake(1);
    pros::delay(350);
    r_Auto.turnToAngle(0.125, 1, 345);
    r_Auto.moveDistance(0.15 ,1, 12);
    r_Auto.turnToAngle(0.125, 1, 45);
    r_Auto.setCatapultDown();
    pros::delay(400);
    r_Auto.setDrivetrain(0.3,0.3);
    pros::delay(450);
    r_Auto.setDrivetrain(0,0);
    pros::delay(2000);
    r_Auto.setCatapultUp();
    r_Auto.setIntake(0);
    // r_Auto.turnToAngle(0.15, 1, 100);
    // r_Auto.moveDistance(0.3, 1, -25);
    // r_Auto.turnToAngle(0.2, 1, 85);
    // r_Auto.setDrivetrain(-0.2, -0.2);
    // pros::delay(500);
    // r_Auto.setDrivetrain(0,0);
    // r_Auto.setDrivetrain(0.5,-0.5);
    // pros::delay(500);
    // r_Auto.setConstraints(0.05, 0.6, 0.9, 0.4, 1, 1.5);
    // r_Auto.manueverToTarget(30, -20, true);

}

void Autonomous_Paths::rightPath() 
{
    r_Auto.setConstraints(0.05, 0.6, 0.4, 1.5);
    r_Auto.setTarget(-10, -20, true);
    r_Auto.manueverToTarget(true, true);
    r_Auto.setConstraints(0.05, 0.4, 0.05, 1);
    r_Auto.setTarget(-10, -100, true);
    r_Auto.manueverToTarget(true, false);
    r_Auto.setDrivetrain(-0.5, -0.5);
    pros::delay(250);
    r_Auto.setDrivetrain(0.3, 0.3);
    pros::delay(700);
    r_Auto.setConstraints(0.05, 0.6, 0.25, 1.5);
    r_Auto.setTarget(15, -3 , false);
    r_Auto.manueverToTarget(true, false);
    r_Auto.deployIntake(true);
    r_Auto.manueverToTarget(false, true);
    r_Auto.setCatapultMid();
    r_Auto.setDrivetrain(0.4, 0.4);
    r_Auto.setIntake(1);
    pros::delay(500);
    r_Auto.setDrivetrain(0, 0);
    pros::delay(250);
    r_Auto.turnToAngle(0.125, 1, 200);
    r_Auto.moveDistance(0.15, 1, 15);
    r_Auto.setIntake(0);
    r_Auto.turnToAngle(0.125, 1, 260);
    r_Auto.moveDistance(0.15, 1, 10);
    r_Auto.setIntake(-1);
    pros::delay(600);
    r_Auto.setDrivetrain(0.5, 0.5);
    pros::delay(300);
    r_Auto.setDrivetrain(-0.4, -0.4);
    r_Auto.setIntake(0);
    pros::delay(500);
    r_Auto.setDrivetrain(0, 0);
    r_Auto.turnToAngle(0.125, 1, 25);
    r_Auto.setDrivetrain(1, 1);
    pros::delay(400);
    r_Auto.setDrivetrain(0.5, 0.5);
    pros::delay(600);
    r_Auto.setDrivetrain(0, 0);
    
}

void Autonomous_Paths::skillsPath() 
{
    r_Auto.setConstraints(0.05, 0.8, 0.05, 1);
    r_Auto.setTarget(11, -16, true);
    r_Auto.manueverToTarget(true, true);
    r_Auto.setConstraints(0.05, 0.4, 0.05, 1);
    r_Auto.setTarget(11, -100, true);
    r_Auto.manueverToTarget(true, false);
    r_Auto.setDrivetrain(-0.6, -0.6);
    pros::delay(250);
    r_Auto.setDrivetrain(0.3, 0.7);
    pros::delay(500);
    r_Auto.setDrivetrain(0,0); 

    r_Auto.turnToAngle(0.125, 1, 320);
    r_Auto.deployIntake(true);
    r_Auto.moveDistance(0.15, 1, 10);
    r_Auto.turnToAngle(0.125, 1, 70);
    r_Auto.setDrivetrain(0.3, 0.3);
    pros::delay(450);
    r_Auto.setDrivetrain(0, 0);
    //launch
    r_Auto.setCatapult(1);
    pros::delay(40000);
    r_Auto.setCatapult(0);
    r_Auto.turnToAngle(.125, 1, 45);
    r_Auto.moveDistance(.4, 1, -48);
    r_Auto.turnToAngle(.125, 1, 85);
    r_Auto.setDrivetrain(-0.7, -0.7);
    pros::delay(800);
    r_Auto.deployExtension(true);
    pros::delay(2000);
    r_Auto.setDrivetrain(0.5, 0.5);
    pros::delay(250);
    r_Auto.setDrivetrain(0, 0);
    // r_Auto.deployIntake(false);
    // r_Auto.turnToAngle(0.15, 1, 100);
    // r_Auto.moveDistance(0.15, 1, -15);
    // r_Auto.turnToAngle(0.15, 1, 90);
    // r_Auto.moveDistance(0.3, 1, -60);

    // r_Auto.deployIntake(true);
    // pros::delay(600);
    // r_Auto.setDrivetrain(0,0); 
    // r_Auto.setCatapultDown();
    // r_Auto.setRequirement(Autonomous_Control::alignYAxis);
    // r_Auto.setTarget(-1, -65, true);
    // r_Auto.manueverToTarget(false, true);
    // r_Auto.setCatapultUp();
    // r_Auto.setIntake(false);
    // r_Auto.setIntake(false);
    
    //break
    // r_Auto.setConstraints(0.05, 0.8, 0.05, 1);
    // r_Auto.setTarget(20, -85, true);
    // r_Auto.manueverToTarget(true, true);
    // r_Auto.setTarget(200, -85, true);
    // r_Auto.manueverToTarget(true, false);
    // r_Auto.setDrivetrain(-0.6, -0.6);
    // pros::delay(250);
    // r_Auto.setDrivetrain(0.3, 0.3);
    // pros::delay(400);
    // r_Auto.setDrivetrain(0,0); 

    

    
    //break
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