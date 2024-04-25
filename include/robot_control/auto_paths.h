#ifndef AUTO_PATHS_H
#define AUTO_PATHS_H
#include "main.h"
#include "Constants.h"
#include "auto_control.h"

class Autonomous_Paths {
    private:

    bool autoWP;

    public:
    Autonomous_Paths(Autonomous_Control& autonomous_Control): r_Auto(autonomous_Control){};
    
    enum auto_path {NONE, TESTING, LEFT_PATH, RIGHT_PATH, SKILLS_PATH, SPECIAL_LEFT_PATH, STATES_LEFT_PATH, STATES_RIGHT_PATH};

    void setAutoWP(bool value);

    bool getAutoWP();

    void test();

    void leftPathWP();

    void leftPathSpecial();

    void leftPathFM();

    void rightPathWP();

    void rightPathFM();

    void skillsPath();

    void statesleftPathFM();

    void statesrightPathFM();

    void setAutoPath(auto_path desiredPath);

    int getAutoPath();

    void printTask();

    private:
    Autonomous_Control& r_Auto;

    auto_path paths;
};

#endif