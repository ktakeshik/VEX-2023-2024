#ifndef AUTO_PATHS_H
#define AUTO_PATHS_H
#include "main.h"
#include "Constants.h"
#include "auto_control.h"

class Autonomous_Paths {
    public:
    Autonomous_Paths(Autonomous_Control& autonomous_Control): r_Auto(autonomous_Control){};

    void test();

    void leftPath();

    void rightPath();

    void printTask();

    private:
    Autonomous_Control& r_Auto;
};

#endif