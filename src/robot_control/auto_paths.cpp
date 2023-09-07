#include "auto_paths.h"
#include "auto_control.h"

void Autonomous_Paths::test() {
    r_Auto.manueverToTarget(-5, -24, true);
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