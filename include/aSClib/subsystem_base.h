#ifndef SUBSYSTEM_BASE_H
#define SUBSYSTEM_BASE_H

using namespace std;

class Subsystem_Base {
    public:

    virtual void shutdown() {}

    virtual void periodic() {}

};
#endif