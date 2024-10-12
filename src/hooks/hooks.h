#include <MinHook.h>

#include "CommandPipe/CommandPipe.h"

namespace Hooks {
    void Install() { 
        MH_Initialize();

        CommandPipe::Install();

        return;
    }
}