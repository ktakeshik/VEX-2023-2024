#include "auto_paths.h"
#include "auto_control.h"

void Autonomous_Paths::test() {
    r_Auto.setTarget(10, 24, 0);
    r_Auto.turnToTarget(0,0);
    r_Auto.moveToTarget(0,0);
}

void Autonomous_Paths::leftPath() {
    
}

void Autonomous_Paths::rightPath() {
    
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