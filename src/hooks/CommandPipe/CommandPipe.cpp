#include "CommandPipe.h"
#include "../../commandmanager.h"

void CommandPipe::Install() {
    REL::Relocation<std::uintptr_t> hookPoint{RELOCATION_ID(52065, 52952), 0x52};
    auto& trampoline = SKSE::GetTrampoline();
    _CompileAndRun = trampoline.write_call<5>(hookPoint.address(), CompileAndRun);
    
    logger::info("Installed hooks for class {}", typeid(CommandPipe).name());
}

void CommandPipe::CompileAndRun(RE::Script* a_script, RE::ScriptCompiler* a_compiler, RE::COMPILER_NAME a_name,
                                RE::TESObjectREFR* a_targetRef) {
    
    if (CommandManager::Dispatch(a_script, a_compiler, a_name, a_targetRef)) return;
    return _CompileAndRun(a_script, a_compiler, a_name, a_targetRef);
}
