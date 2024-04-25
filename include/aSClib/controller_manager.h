#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H
#include <vector>
#include "button_binding.h"
#include "joystick_binding.h"
#include "main.h"
#include <algorithm>

using namespace std;

class Controller_Manager {
    vector<Button_Binding*> digitalBindings;
    vector<Joystick_Binding*> analogBindings;

    public:

    Controller_Manager& addBinding(Button_Binding* buttonBinding) {
        digitalBindings.emplace_back(buttonBinding);
        return *this;
    }

    Controller_Manager& addBinding(Joystick_Binding* joystickBinding) {
        analogBindings.emplace_back(joystickBinding);
        return *this;
    }

    private:

    void checkButtongBindings() {
        if (digitalBindings.size() == 0) {
            return;
        }

        for (Button_Binding* binding : digitalBindings) {
            binding->run();
        }
    }

    void checkAnalogBindings() {
        if (analogBindings.size() == 0) {
            return;
        }
        
        for (Joystick_Binding* binding : analogBindings) {
            binding->run();
        }
    }

    public:

    void run() {
        checkAnalogBindings();
        checkButtongBindings();
    }
    
};

#endif