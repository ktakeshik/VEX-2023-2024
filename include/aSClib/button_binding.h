#ifndef BUTTON_BINDING_H
#define BUTTON_BINDING_H
#include <vector>
#include "command_base.h"
#include "command_scheduler.h"
#include "main.h"

class Button_Binding {
    Command_Scheduler* scheduler;

    pros::Controller controller;
    pros::controller_digital_e_t key;
    vector<Command_Base*> onTrueCommands;
    vector<Command_Base*> onFalseCommands;

    public:

    Button_Binding(Command_Scheduler* scheduler, pros::Controller controller, pros::controller_digital_e_t key)
        : scheduler(scheduler), controller(controller), key(key) 
    { };

    Button_Binding& onTrue(Command_Base* command) {
        onTrueCommands.emplace_back(command);
        return *this;
    }

    Button_Binding& onFalse(Command_Base* command) {
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
        return controller.get_digital_new_press(key);
    }

};

#endif