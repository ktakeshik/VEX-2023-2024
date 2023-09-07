#include "auto_paths.h"
#include "auto_control.h"

void Autonomous_Paths::test() {
    r_Auto.launchCatapult();
}

void Autonomous_Paths::leftPath() {
    
}

void Autonomous_Paths::rightPath() {
    
    r_Auto.setTarget(0, 24, 0, false);
    r_Auto.turnToTarget(0.05, 1, 0.9);
    r_Auto.moveToTarget(0.15, 1, 1.5);
    r_Auto.deployIntake(true);
    r_Auto.setIntake(-1);
    
}

void Autonomous_Paths::skillsPath() {

}

void Autonomous_Paths::setAutoPath(auto_path desiredPath) {
    paths = desiredPath;
}

int Autonomous_Paths::getAutoPath() {
    return paths;
}

void Autonomous_Paths::printTask() {
    
}