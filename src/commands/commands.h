#include "../commandmanager.h"

class LeveledListUp;
class AutoReadPick;
class EnhancedCrafting;

namespace Commands {
	void Install() {

#define cmd                                                                                     \
					const std::vector<std::string> &args, RE::Script *a_script, RE::ScriptCompiler *a_compiler, \
						RE::COMPILER_NAME a_name, RE::TESObjectREFR *a_targetRef
#define PRINT RE::ConsoleLog::GetSingleton()->Print

		CommandManager::Register("ResetCurrentCell", [](cmd) {
			if (args.size() != 1) {
				PRINT("Usage: ResetCurrentCell <save/commit>");
				return;
			}

			//auto&& vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
			//auto&& handlePolicy = vm->handlePolicy;
			static RE::TESObjectCELL* SavedCell;

			if (args[0] == "commit") {
				const auto&& scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
				const auto&& script = scriptFactory ? scriptFactory->Create() : nullptr;
				if (script) {
					script->SetCommand("pcb");

					RE::ScriptCompiler compiler;
					using func_t = void(RE::Script* script, RE::ScriptCompiler* compiler, RE::COMPILER_NAME name, RE::TESObjectREFR* targetRef);
					REL::Relocation<func_t> func{ RELOCATION_ID(21416, REL::Module::get().version().patch() < 1130 ? 21890 : 441582) };
					func(script, &compiler, RE::COMPILER_NAME::kSystemWindowCompiler, nullptr);

					script->SetCommand("ResetInterior " + std::string(SavedCell->GetFormEditorID()));
					func(script, &compiler, RE::COMPILER_NAME::kSystemWindowCompiler, nullptr);

					delete script;
				}

				//RE::VMHandle cell = handlePolicy->GetHandleForObject(SavedCell->GetFormType(), SavedCell);
				//RE::BSTSmartPointer<RE::BSScript::Object> cellObj;
				//vm->FindBoundObject(cell, "Cell", cellObj);

				//auto callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>();
				//auto a_args = RE::MakeFunctionArguments();
				//const RE::BSFixedString fnName = "Reset";
				//vm->DispatchMethodCall(cellObj, fnName, a_args, callback);

				PRINT("Committed Cell %s", SavedCell->GetFullName());
				return;
			}
			

			SavedCell = RE::PlayerCharacter::GetSingleton()->GetParentCell();
			PRINT("Saved Cell %s", SavedCell->GetFullName());
			return;
			});

#undef cmd
	}

}