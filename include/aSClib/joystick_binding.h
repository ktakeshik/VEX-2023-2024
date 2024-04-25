#ifndef JOYSTICK_BINDING_H
#define JOYSTICK_BINDING_H
#include "command_base.h"
#include "command_scheduler.h"
#include "main.h"

class Joystick_Binding {
    Command_Scheduler *scheduler;

    pros::Controller controller;
    pros::controller_analog_e_t key;
    float deadband;
    vector<Command_Base*> onTrueCommands;
    vector<Command_Base*> onFalseCommands;

    public:

    Joystick_Binding(Command_Scheduler* scheduler, pros::Controller controller, pros::controller_analog_e_t key, float deadband)
        : scheduler(scheduler), controller(controller), key(key), deadband(deadband)
    { };
    
    Joystick_Binding& onTrue(Command_Base* command) {
        onTrueCommands.emplace_back(command);
        return *this;
    }

    Joystick_Binding& onFalse(Command_Base* command) {
        onFalseCommands.emplace_back(command);
        return *this;
    }
    
    void run() {
        if(!checkBinding()) {
            for (Command_Base* i : onFalseCommands) {
                scheduler->addCommand(i);
            }
            return;
        }
        for (Command_Base* i : onTrueCommands) {
            scheduler->addCommand(i);
        }
    }

    private: 

    bool checkBinding() {
        return (abs(controller.get_analog(key)) > deadband) ? true : false;
    }

};

#endif