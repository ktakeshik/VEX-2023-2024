#ifndef CATAPULT_SUBSYSTEM_H
#define CATAPULT_SUBSYSTEM_H
#include "main.h"
#include "Constants.h"

class Catapult_Subsystem {
    private:
    //Motors
    pros::Motor m_catapult;

    //Sensors
    pros::Rotation s_rotation;

    public:

    //variables
    bool saftey;
    enum catapult_state {DEFAULT_STATE, LAUNCH_TRIBALL, POSSESS_TRIBALL, MATCH_LOAD, STAY_UP};

    private: 
    catapult_state cata_status;

    public:
    
    Catapult_Subsystem();

    bool isCatapultDown();

    bool isCatapultMiddle();

    bool isCatapultUp();

    void setSaftey(bool value);

    void toggleSaftey();

    bool getSaftey();

    void setCatapultState(catapult_state status);

    int getCatapultState();

    void catapultControl(float percentOut);

    void stopCatapult();

    void printTask();
};

#endif