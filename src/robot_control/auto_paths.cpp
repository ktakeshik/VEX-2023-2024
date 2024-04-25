#include "robot_control\auto_paths.h"
#include "robot_control\auto_control.h"

void Autonomous_Paths::setAutoWP(bool value)
{
    autoWP = {value};
}

bool Autonomous_Paths::getAutoWP()
{
    return autoWP;
}

void Autonomous_Paths::test() 
{
    pros::delay(3000);
    r_Auto.turnToHeading(0.05, 0.5, 270);
}

void Autonomous_Paths::leftPathWP() 
{
    /************************************************\
    *                                                *
    *  Code for Qualification Match: Far Win Point   *
    *                                                *
    \************************************************/

    // 1. Push Alliance Triball into Goal. +5 pts
        r_Auto.turnToAngle(0.05, 0.6, -28);
        r_Auto.moveDistance(0.05, 0.3, -25);
        r_Auto.turnToHeading(0.05, 1, 0);
        r_Auto.setDrivetrain(-0.6, -0.6);
        pros::delay(500);
        r_Auto.setDrivetrain(0,0);
        pros::delay(200);
    // 2. Move to Match Load Bar and collect Triball. 1 of 3 AWP tasks
        r_Auto.moveDistance(0.05, 0.6, 4.5);
        r_Auto.turnToAngle(0.05, 1, -60);
        r_Auto.moveDistance(0.05, 0.6, 12);
        r_Auto.turnToAngle(0.05, 1, 105);
        r_Auto.deployIntake(true);
        r_Auto.setIntake(1);
        r_Auto.setCatapultDown();
        pros::delay(200);
        r_Auto.moveDistance(0.05, 0.5, 9.5);
        pros::delay(1400);
    // 3. Launch Triball over Long Barrier into Offensive Zone. +2 pts
        r_Auto.moveDistance(0.05, 0.6, -31);
        r_Auto.setCatapultUp();
        pros::delay(400);
    // 4. Move to Red Elevation Bar Lane and push Triball in Offensive Zone. +2 pts
        r_Auto.moveDistance(0.05, 0.6, 21);
        r_Auto.setIntake(0);
        r_Auto.deployIntake(false);
        pros::delay(300);
        r_Auto.turnToAngle(0.05, 0.6, -80);
        r_Auto.moveDistance(0.05, 0.4, 15);
        r_Auto.turnToHeading(0.05, 0.5, 271);
    // 5. Touch horizontal Elevation Bar. 2 of 3 AWP tasks 
        r_Auto.setDrivetrain(0.9, 0.9);
        pros::delay(500);
        r_Auto.setDrivetrain(0.1, 0.1);
        pros::delay(1000);
        r_Auto.setDrivetrain(0,0);
}

void Autonomous_Paths::leftPathSpecial() {
    r_Auto.turnToHeading(0.05, 0.4, 327);
    pros::delay(200);
    r_Auto.setCatapultUp();
    pros::delay(400);
    r_Auto.setCatapultDown();
    pros::delay(400);
    r_Auto.turnToHeading(0.05, 0.6, 270);
    r_Auto.moveDistance(.05, 0.6, -8);
    r_Auto.turnToHeading(.05, 0.6, 315);
    r_Auto.deployIntake(true);   
    r_Auto.setIntake(1);
    pros::delay(200);
    r_Auto.moveDistance(.05, 0.6, 15);
    pros::delay(1400);
    r_Auto.moveDistance(.05, 0.6, -15);
    pros::delay(400);
    r_Auto.turnToHeading(.05, 0.6, 320);
    r_Auto.setCatapultUp();
    pros::delay(300);
    r_Auto.setCatapultDown();
    r_Auto.setIntake(0);
    r_Auto.deployIntake(false);
    r_Auto.turnToHeading(0.05, 0.6, 270);
    r_Auto.moveDistance(0.05, 0.8, 10);
    r_Auto.turnToHeading(0.05, 0.6, 183);
    r_Auto.setDrivetrain(0.6, 0.6);
    pros::delay(1000);
    r_Auto.setDrivetrain(0.1, 0.1);
    pros::delay(500);
    r_Auto.setDrivetrain(0,0);
}

void Autonomous_Paths::leftPathFM()
{
    /************************************************\
    *                                                *
    *   Code for Elimination Match: Far Win Point    *
    *                                                *
    \************************************************/

    // 1. Collect Triball in Neutral Zone and move back near starting position.
        r_Auto.turnToAngle(0.05, 0.5, 11);
        r_Auto.deployIntake(true);
        r_Auto.setIntake(1);
        pros::delay(200);
        r_Auto.setCatapultDown();
        r_Auto.moveDistance(0.05, 1, 43);
        pros::delay(800);
        r_Auto.moveDistance(0.05, 0.6, -8);
        r_Auto.turnToAngle(0.05, 0.6, -150);
    // 2. Launch Triball over to Offensive Zone. +2 pts
        pros::delay(200);
        r_Auto.setCatapultUp();
        r_Auto.setIntake(0);
        pros::delay(200);
        r_Auto.setCatapultDown();
    // 3. Collect Triball in Neutral Zone near Long Barrier 
    // and move back near starting position.
        r_Auto.turnToAngle(0.05, 0.6, 185);
        r_Auto.setIntake(1);
        r_Auto.moveDistance(0.05, 0.6, 21);
        pros::delay(800);
        r_Auto.moveDistance(0.05, 0.6, -10);
        r_Auto.turnToAngle(0.05, 0.6, -165);
    // 4. Launch Triball over to Offensive Zone. +2 pts
        r_Auto.setCatapultUp();
        pros::delay(300);
        r_Auto.setIntake(0);
        r_Auto.deployIntake(false);
    // 5. Move to Red Elevation Bar and make contact, 
    // pushing the Triball directly under into Offensive Zone. +2 pts
        r_Auto.turnToAngle(0.05, 0.6, -42);
        r_Auto.moveDistance(0.05, .8, 42.5);
        r_Auto.turnToHeading(0.05, 0.6, 93); 
        r_Auto.setDrivetrain(0.6, 0.6);
        pros::delay(950); 
        r_Auto.setDrivetrain(0.05, 0.05);
        pros::delay(2100);
        r_Auto.setDrivetrain(0,0);
}

void Autonomous_Paths::rightPathWP() 
{
    /************************************************\
    *                                                *
    *  Code for Qualification Match: Near Win Point  *
    *                                                *
    \************************************************/

    // 1. Push Alliance  AT  Triball into Red Goal. +5 pts, 1 of 3 AWP tasks
        r_Auto.turnToAngle(0.05, 0.6, 28);
        r_Auto.moveDistance(0.05, 0.2, -25);
        r_Auto.turnToHeading(0.05, 1, 0);
        r_Auto.moveDistance(0.05, 0.6, -5);
        pros::delay(200);
    // 2. Collect Triball near Long Barrier.
        r_Auto.moveDistance(0.05, 0.6, 4);
        r_Auto.turnToAngle(0.05, 1, 110);
        r_Auto.deployIntake(true);
        pros::delay(100);
        r_Auto.setIntake(1);
        r_Auto.setCatapultMid();
        r_Auto.moveDistance(0.05, 0.6, 43);
        pros::delay(1000);
        r_Auto.setIntake(0);
    // 3. Move to contact Vertical Bar. 2 of 3 AWP tasks
        r_Auto.turnToAngle(0.05, 1, -65);
        r_Auto.setDrivetrain(0.4, 0.4);
        pros::delay(2000);
        r_Auto.setDrivetrain(0,0);    
}

void Autonomous_Paths::rightPathFM()
{
    /************************************************\
    *                                                *
    *   Code for Elimination Match: Near Win Point   *
    *                                                *
    \************************************************/

    // 1. Move in front of goal and outtake Alliance Triball into Goal. 
        r_Auto.turnToAngle(0.05, 0.7, -30);
        r_Auto.moveDistance(0.05, 1, -36);
        r_Auto.turnToAngle(0.05, 0.7, -75);
        r_Auto.setIntake(-1);
        r_Auto.deployIntake(true);
        pros::delay(600);
        r_Auto.moveDistance(0.05, 0.6, 5);
        pros::delay(500);
    // 2. Collect Triball near Long Barrier and deposit near Goal. 
        r_Auto.moveDistance(0.05, 0.6, -1.5);
        r_Auto.turnToAngle(0.05, 0.7, 177);
        r_Auto.setIntake(1);
        r_Auto.moveDistance(0.05, 0.6, 14);
        pros::delay(300);
        r_Auto.moveDistance(0.05, 0.6, -8);
        r_Auto.setIntake(0);
        r_Auto.turnToAngle(0.05, 0.7, -178);
        r_Auto.setIntake(-1);
        pros::delay(500);
    // 3. Collect Triball in Neutral Zone closer to Long Barrier 
    // and deposit near Goal.
        r_Auto.moveDistance(0.05, 0.6, -5);
        r_Auto.turnToAngle(0.05, 0.7, -110);
        r_Auto.setIntake(1);
        r_Auto.moveDistance(0.05, 0.6, 15);
        pros::delay(500);
        r_Auto.moveDistance(.05,.6, -2);
        r_Auto.turnToHeading(0.05, 0.7, -90);
        r_Auto.setIntake(-1);
        pros::delay(750);
    // 4. Push all Triballs, including the 2nd Triball in Neutral Zone, 
    // into Goal. +20 pts
        r_Auto.deployIntake(false);
        r_Auto.deployExtension(true);
        pros::delay(250);
        r_Auto.setDrivetrain(1, 1);
        pros::delay(850);
        r_Auto.setDrivetrain(0, 0);
        pros::delay(100);
        r_Auto.deployExtension(false);
        r_Auto.setDrivetrain(-0.4, -0.4);
        pros::delay(750);
        r_Auto.setDrivetrain(0, 0);
}

void Autonomous_Paths::skillsPath() 
{
    /************************************************\
    *                                                *
    *            Skills: Autonomous Coding           *
    *                                                *
    \************************************************/

    // 1. Push two  AT  Alliance Triballs into Goal.
        r_Auto.turnToAngle(0.05, 0.4, -32);
        r_Auto.moveDistance(0.05, 0.4, -21);
        r_Auto.turnToAngle(0.05, 1, 26);
        r_Auto.moveDistance(0.05, 0.8, -5);
        r_Auto.setDrivetrain(0.3, 0.3);
        pros::delay(20);
        r_Auto.setDrivetrain(0,0);
    // 2. Match Load and shoot 44  ML Triballs into Offensive Zone 
    // between the Red Goal and Red Elevation Bar. 
        r_Auto.turnToAngle(0.05, 1, -45);
        r_Auto.moveDistance(0.05, 0.6, 17);
        r_Auto.turnToAngle(0.05, 1, 125);
        r_Auto.setDrivetrain(0.4, 0.4);
        pros::delay(600);
        r_Auto.setDrivetrain(0, 0);
        r_Auto.setCatapult(1);
        // pros::delay(32500);
        pros::delay(2500);
        r_Auto.setCatapult(0);
        r_Auto.setCatapultDown();
    // 3. Move to Offensive Zone.
        r_Auto.moveDistance(0.05, 0.4, -5);
        r_Auto.turnToAngle(.125, 1, 50);
        r_Auto.deployIntake(true);
        r_Auto.moveDistance(0.05, 0.6, -24);
        r_Auto.turnToHeading(0.05, 1, 91);
        r_Auto.moveDistance(0.05, 0.7, -67);
        r_Auto.turnToHeading(0.05, 1, 76);
        r_Auto.moveDistance(0.05, 0.6, -13);
        r_Auto.deployIntake(false);
        r_Auto.turnToHeading(0.05, 1, 37);
        r_Auto.moveDistance(0.05, 1, -10);
        r_Auto.turnToHeading(0.05, 1, 22);
        r_Auto.moveDistance(0.05, 1, -10);
    // 4. Shove Triballs into side of Goal (2 passes).
        // r_Auto.setDrivetrain(0.4, 0.4);
        // pros::delay(500);
        // r_Auto.setDrivetrain(0,0);
        // r_Auto.turnToHeading(0.05, 1, 0);
        // pros::delay(250);
        // r_Auto.setDrivetrain(-0.8, -0.8);
        // pros::delay(800);
        r_Auto.setDrivetrain(0,0); 
        pros::delay(250);
        r_Auto.moveDistance(0.05, 0.6, 6);
    // 5. Shove Triballs into front of Goal (2 passes).
        // r_Auto.turnToHeading(0.05, 0.6, 275);
        // r_Auto.moveDistance(0.05, 0.6, -35);
        r_Auto.turnToHeading(0.05, 0.6, 310);
        r_Auto.moveDistance(0.05, 0.6, -55);
        // r_Auto.moveDistance(0.05, 0.6, 10);
        // r_Auto.turnToHeading(0.05, 0.6, 290);
        // r_Auto.moveDistance(0.05, 0.6, -18);
        r_Auto.turnToHeading(0.05, 1, 250);
        // r_Auto.deployExtension(true);
        r_Auto.setDrivetrain(0.7, 0.7);
        pros::delay(1500);
        r_Auto.setDrivetrain(0,0);
        // r_Auto.turnToHeading(0.05, 1, 0);
        // pros::delay(250);
        r_Auto.setDrivetrain(-0.4, -0.4);
        pros::delay(300);
        r_Auto.setDrivetrain(0.0, 0.0);
        r_Auto.deployExtension(false);
        r_Auto.turnToHeading(0.05, 1, 270);
        r_Auto.moveDistance(0.05, 0.6, -27);
        r_Auto.turnToHeading(0.05, 1, 0);
        r_Auto.moveDistance(0.05, 0.6, -30);
        r_Auto.turnToHeading(0.05, 1, 305);
        r_Auto.deployExtension(true);
        r_Auto.setDrivetrain(1, 1);
        pros::delay(1300);
        r_Auto.deployExtension(false);
        r_Auto.setDrivetrain(-0.3, -0.3);
        pros::delay(800);
        r_Auto.setDrivetrain(0, 0);
} 

void Autonomous_Paths::statesleftPathFM()
{
    r_Auto.turnToAngle(0.05, 0.5, 4);
    r_Auto.moveDistance(0.05, 0.8, 45);
    r_Auto.setIntake(1);
    r_Auto.deployIntake(true);
    pros::delay(500);
    r_Auto.setCatapultMid();
    r_Auto.turnToHeading(0.05, 0.8, 91);
    r_Auto.deployExtension(true);
    pros::delay(200);
    r_Auto.moveDistance(0.05, 1, 21);
    r_Auto.setIntake(-1);
    pros::delay(500);
    r_Auto.deployExtension(false);
    r_Auto.setIntake(0);
    r_Auto.setDrivetrain(-0.8, -0.82);
    pros::delay(1400);
    r_Auto.setDrivetrain(0, 0);
    pros::delay(200);
    r_Auto.moveDistance(0.05, 0.6, 27);
    r_Auto.turnToHeading(0.05, 0.6, 216);
    r_Auto.moveDistance(0.05, 0.6, 58);
    r_Auto.turnToHeading(0.05, 0.5, 110);
    r_Auto.deployIntake(false);
    r_Auto.setDrivetrain(0.6, 0.6);
    pros::delay(1600); 
    r_Auto.setDrivetrain(-0.6, -0.6);
    pros::delay(1000); 
    r_Auto.setDrivetrain(0, 0);
    r_Auto.turnToHeading(0.05, 0.5, 270);
}

void Autonomous_Paths::statesrightPathFM()
{
    r_Auto.deployIntake(true);
    r_Auto.setIntake(1);
    r_Auto.moveDistance(0.05, 0.3, 6);
    pros::delay(350);
    r_Auto.moveDistance(0.05, 0.8, -14);
    r_Auto.turnToAngle(0.05, 0.6, -25);
    r_Auto.moveDistance(.05, 0.6, -20);
    r_Auto.moveDistance(.05, 0.3, -12);
    r_Auto.setIntake(-1);
    r_Auto.turnToHeading(0.05, 0.5, -245);
    r_Auto.deployIntake(false);
    pros::delay(400);
    r_Auto.setDrivetrain(0.8, 0.8);
    pros::delay(600);
    r_Auto.setDrivetrain(0, 0);
    r_Auto.setIntake(0);
    r_Auto.moveDistance(0.05, .8, -5);
    r_Auto.deployIntake(true);
    r_Auto.turnToHeading(0.05, 1, 27);
    r_Auto.setIntake(1);
    r_Auto.moveDistance(0.05, 1, 43);
    pros::delay(400);
    r_Auto.setIntake(-1);
    r_Auto.turnToHeading(0.05, 1, 150);
    r_Auto.moveDistance(0.05, 1, 8);
    pros::delay(400);
    r_Auto.turnToHeading(0.05, 1, 40);
    r_Auto.setIntake(1);
    r_Auto.moveDistance(0.05, 1, 14);
    pros::delay(400);
    r_Auto.turnToHeading(0.05, 1, 180);
    r_Auto.setIntake(-1);
    pros::delay(250);
    r_Auto.deployIntake(false);
    r_Auto.deployExtension(true);
    pros::delay(250);
    r_Auto.setDrivetrain(1, 1);
    pros::delay(850);
    r_Auto.setDrivetrain(0, 0);
    r_Auto.setIntake(0);
    pros::delay(100);
    r_Auto.deployExtension(false);
    r_Auto.setDrivetrain(-0.4, -0.4);
    pros::delay(750);
    r_Auto.setDrivetrain(0, 0);
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