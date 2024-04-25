#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H
#include "subsystem_base.h"
#include <vector>

using namespace std;

class Command_Base {
    public:
    vector<Subsystem_Base*> requiredSubsystems;
    
    virtual vector<Subsystem_Base*> getRequirements() {
        return requiredSubsystems;
    }

    virtual void addRequirement(Subsystem_Base* subsystem) {
        requiredSubsystems.emplace_back(subsystem);
    };

    virtual void initialize() {}

    virtual void execute() {}

    virtual void end() {}

    virtual bool isFinished() {return false;}

    virtual void disabled() {}

    virtual void run() {
        if (!isFinished()) {
            execute();
        }
        else {
            end();
        }
    }
};

#endif