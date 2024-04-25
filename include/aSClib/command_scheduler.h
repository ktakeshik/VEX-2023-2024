#ifndef COMMAND_SCHEDULER_H
#define COMMAND_SCHEDULER_H
#include "subsystem_base.h"
#include "command_base.h"
#include "main.h"
#include <algorithm>

using namespace std;

class Command_Scheduler {
    vector<Subsystem_Base*> runningSubsystems;
    vector<Subsystem_Base*> subsystems;
    vector<Command_Base*> defaultCommands;
    vector<Command_Base*> scheduledCommands;
    vector<Command_Base*> runningCommands;

    public:

    Command_Scheduler& assignSubsystem(Subsystem_Base* subsystem) {
        subsystems.emplace_back(subsystem);
        return *this;
    }

    Command_Scheduler& scheduleDefaultCommand(Command_Base* command) {
        defaultCommands.emplace_back(command);
        return *this;
    }

    void addCommand(Command_Base* command) {
        command->initialize();
        scheduledCommands.emplace_back(command);
    }

    private:

    bool isContained(vector<Subsystem_Base*> subsystems, Subsystem_Base* value) {
        return count(subsystems.begin(), subsystems.end(), value);
    }

    bool isContained(vector<Command_Base*> commands, Command_Base* value) {
        return count(commands.begin(), commands.end(), value);
    }

    void removeValue(vector<Subsystem_Base*> subsystems, Subsystem_Base* value) {
        subsystems.erase(remove(subsystems.begin(), subsystems.end(), value), subsystems.end());
    }

    void removeValue(vector<Command_Base*> commands, Command_Base* value) {
        commands.erase(remove(commands.begin(), commands.end(), value), commands.end());
    }

    void queueCommand(Command_Base* command) {
        runningCommands.emplace_back(command);
    }

    bool isCommandRunning(Command_Base* command) {
        return isContained(runningCommands, command);
    }

    bool isCommandFinished(Command_Base* command) {
        if (command->isFinished()) {
            return true;
        }
        return false;
    }

    void removeCommand(Command_Base* command) {
        removeValue(scheduledCommands, command);
        if (isCommandRunning(command)){
            removeValue(runningCommands, command);
        }
    }

    void addRequirements(vector<Subsystem_Base*> requiredSubsystems) {
        for (Subsystem_Base* subsystem : requiredSubsystems) {
            runningSubsystems.emplace_back(subsystem);
        }
    }

    bool isSubsystemRunning(vector<Subsystem_Base*> requiredSubsystems) {
        for (Subsystem_Base* subsystem : requiredSubsystems) {
            if (isContained(runningSubsystems, subsystem)) {
                return true;
            }
        }
        return false;
    }

    void runCommands() {
        for (Command_Base* command : scheduledCommands) {
            if (isCommandFinished(command)) {
                removeCommand(command);
                continue;
            }
            else if (isCommandRunning(command))
            {
                command->run();
                continue;
            }

            if (isSubsystemRunning(command->getRequirements())) {
                continue;
            }
            else {
                addRequirements(command->getRequirements());
                queueCommand(command);
                command->run();
            }
        }
    }

    void runDefaultCommands() {
        for (Command_Base* command : defaultCommands) {
            command->run();
        }
    }


    void runPeriodic() {
        for (Subsystem_Base* subsystem : subsystems) {
            subsystem->periodic();
        }
    }

    public:

    void run() {
        runDefaultCommands();
        runCommands();
        runPeriodic();
    }

    void shutdown() {
        for (Subsystem_Base* subsystem : subsystems) {
            subsystem->shutdown();
        }
    }

};
#endif